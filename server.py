from http.server import BaseHTTPRequestHandler, HTTPServer
import json
import time

# Read local json file
def read_json_file(fname):
    with open(fname) as f:
        data = json.load(f)
    return data


# HTTPRequestHandler class
class testHTTPServer_RequestHandler(BaseHTTPRequestHandler):

    # GET JSON Data Endpoint
    def do_GET(self):
        if self.path == '/data':
            try:
                # Send message back to client
                result = read_json_file('./data.json')

                # Send response status code
                self.send_response(200)

                # Send headers
                self.send_header('Content-type', 'application/json')
                self.end_headers()

                json_str = json.dumps(result)
                # Write content as utf-8 data
                self.wfile.write(bytes(json_str, "utf8"))
            except Exception as err:
                print(err)
                self.send_error(500)


def run():
    print('starting server...')

    # Server settings (can change port # if conflicting)
    server_address = ('0.0.0.0', 8081)
    httpd = HTTPServer(server_address, testHTTPServer_RequestHandler)
    print('running server...')
    httpd.serve_forever()

run()
