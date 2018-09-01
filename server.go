package anhttp

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net"
	"net/url"
	"strings"
)

// This type is used to describe an anhttp server this is going to be run.
type Config struct {
	Name    string
	Address string

	Handler Handler
}

func (c *Config) setDefaults() {
	if c.Name == "" {
		c.Name = "anhttp-server"
	}
	if c.Address == "" {
		c.Address = "localhost:12345"
	}
	if c.Handler == nil {
		c.Handler = DefaultHandler
	}
}

// These are the valid HTTP methods recognized by this server.
const (
	MethodGet    string = "GET"
	MethodPut           = "PUT"
	MethodPost          = "POST"
	MethodDelete        = "DELETE"
)

var methods = []string{
	MethodGet,
	MethodPut,
	MethodPost,
	MethodDelete,
}

// This type describes an HTTP request.
type Request struct {
	Method  string
	URL     *url.URL
	Headers map[string]string
	Body    bytes.Buffer
}

// These are the valid HTTP codes recognized by this server.
const (
	StatusOK int = 200
)

var statusStrings = map[int]string{
	StatusOK: "OK",
}

// This type describes an HTTP response.
type Response struct {
	Status  int
	Headers map[string]string
	Body    bytes.Buffer
}

// This type is used to handle the incoming HTTP requests.
type Handler func(rsp *Response, req *Request)

// This function is the default Handler that simply logs stuff to stdout.
func DefaultHandler(rsp *Response, req *Request) {
	log.Printf("DefaultHandler: %s %s", req.Method, req.URL.String())
	log.Printf("DefaultHandler: %s", req.Headers)

	if body, err := ioutil.ReadAll(&req.Body); err != nil {
		log.Printf("  Body: ??? (%s)", err.Error())
	} else {
		log.Printf("  Body: %q", body)
	}

	fmt.Fprintln(&rsp.Body, "Hello...yeah")
}

// Open a listener socket and run the server described by the provided
// config. This function will block until something back happens. This
// function will always return a non-nil error.
func ListenAndServe(config *Config) error {
	config.setDefaults()

	log.Printf("Starting server %s", config.Name)

	l, err := net.Listen("tcp", "localhost:12345")
	if err != nil {
		log.Fatal(err)
	}
	log.Printf("Created listener on address %s", "localhost:12345")

	for {
		conn, err := l.Accept()
		if err != nil {
			log.Fatal(err)
		}
		go handleConn(config, conn)
	}
}

func handleConn(config *Config, conn net.Conn) {
	defer conn.Close()
	log.Printf("Handling conn from %s", conn.RemoteAddr())

	// TODO: set connection timeout

	var req Request
	if err := unmarshalRequest(conn, &req); err != nil {
		log.Printf("Cannot unmarshal Request: %s", err.Error())
		return
	}

	var rsp Response
	rsp.Status = StatusOK
	config.Handler(&rsp, &req)

	if err := marshalResponse(&req, &rsp, conn); err != nil {
		log.Printf("Cannot marshal Response: %s", err.Error())
		return
	}
}

func marshalResponse(req *Request, rsp *Response, connection io.Writer) error {
	_, err := fmt.Fprintf(connection, "%s %d %s\r\n",
		"HTTP/1.1", rsp.Status, statusStrings[rsp.Status])
	if err != nil {
		return err
	}

	for key, value := range rsp.Headers {
		if err := marshalHeader(key, value, connection); err != nil {
			return err
		}
	}

	if _, err := fmt.Fprintf(connection, "\r\n\r\n"); err != nil {
		return err
	}

	if _, err := io.Copy(connection, &rsp.Body); err != nil {
		return err
	}

	return nil
}

func marshalHeader(key, value string, connection io.Writer) error {
	_, err := fmt.Fprintf(connection, "%s: %s\r\n", key, value)
	return err
}

func unmarshalRequest(payload io.Reader, req *Request) error {
	scanner := bufio.NewScanner(payload)
	scanner.Split(bufio.ScanLines)

	if err := unmarshalMethodPathVersion(scanner, req); err != nil {
		return err
	}

	req.Headers = make(map[string]string)
	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			break
		}

		if err := unmarshalHeader(line, req); err != nil {
			return err
		}
	}
	if err := scanner.Err(); err != nil {
		return err
	}

	if req.Method != "GET" {
		io.Copy(&req.Body, payload)
	}

	return nil
}

func unmarshalMethodPathVersion(scanner *bufio.Scanner, req *Request) error {
	if !scanner.Scan() {
		return scanner.Err()
	}
	line := scanner.Text()

	wordScanner := bufio.NewScanner(strings.NewReader(line))
	wordScanner.Split(bufio.ScanWords)
	if !wordScanner.Scan() {
		if err := wordScanner.Err(); err != nil {
			return err
		} else {
			return fmt.Errorf("Could not find method in '%s'", line)
		}
	}
	method := wordScanner.Text()

	if !wordScanner.Scan() {
		if err := wordScanner.Err(); err != nil {
			return err
		} else {
			return fmt.Errorf("Could not find path in '%s'", line)
		}
	}
	path := wordScanner.Text()

	if !wordScanner.Scan() {
		if err := wordScanner.Err(); err != nil {
			return err
		} else {
			return fmt.Errorf("Could not find version in '%s'", line)
		}
	}
	version := wordScanner.Text()

	req.Method = ""
	for _, m := range methods {
		if strings.HasPrefix(method, m) {
			req.Method = method
			break
		}
	}
	if req.Method == "" {
		return fmt.Errorf("Invalid method: %s", string(method))
	}

	var err error
	req.URL, err = url.Parse(path)
	if err != nil {
		return fmt.Errorf("Cannot parse path '%s': %s", path, err.Error())
	}

	if version != "HTTP/1.1" {
		return fmt.Errorf("Invalid version: got %s, expected HTTP/1.1", version)
	}

	return nil
}

func unmarshalHeader(line string, req *Request) error {
	keyValue := strings.SplitN(line, ":", 2)
	if len(keyValue) != 2 {
		return fmt.Errorf("Failed to unmarshal header from '%s'", line)
	}

	req.Headers[strings.Trim(keyValue[0], " ")] = strings.Trim(keyValue[1], " ")

	return nil

}
