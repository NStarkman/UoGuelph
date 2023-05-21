#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
import os
from http.server import HTTPServer, BaseHTTPRequestHandler
from MolDisplay import Molecule

# Create a class that is a subclass of the BaseHTTPRequestHandler class.
class MyHandler(BaseHTTPRequestHandler):
    
    # Create a do_GET method that returns a 200 OK response with the home_page HTML.
    def do_GET(self):
        if self.path == '/':
            self.send_response(200)  # OK
            self.send_header('Content-type', 'text/html')
            self.send_header('Content-length', len(self.home_page))
            self.end_headers()
            self.wfile.write(bytes(self.home_page, 'utf-8'))
        else:
            self.send_response(404)
            self.end_headers()
            self.wfile.write(bytes('404: not found', 'utf-8'))

    # Create a do_POST method that returns a 200 OK response with the molecule image.
    def do_POST(self):
        if self.path == '/molecule':
            content_type = self.headers.get('Content-type')
            content_length = int(self.headers.get('Content-length'))

            # Check if content type is multipart/form-data
            if content_type.startswith('multipart/form-data'):
                data = self.rfile.read(content_length)
                lines = data.decode('utf-8').split('\n')[4:]
                # Check if file is selected
                if lines[0].startswith('\r'):
                    self.send_response(400)
                    self.end_headers()
                    self.wfile.write(bytes('400: Bad Request. No file selected', 'utf-8'))
                    return              
                
                with open('moleculeImageBuffer.sdf', 'w', encoding='utf-8') as file:
                    for line in lines:
                        file.write(line + "\n")
                
                with open('moleculeImageBuffer.sdf',  encoding='utf-8') as file:
                    mol = Molecule()
                    mol.parse(file)
                    mol.sort()
                    svg = Molecule.svg(mol)
                self.send_response(200)
                self.send_header('Content-type', 'image/svg+xml')
                self.send_header('Content-length', len(svg))
                self.end_headers()
                self.wfile.write(bytes(svg, 'utf-8'))
            else:
                self.send_response(400)
                self.end_headers()
                self.wfile.write(bytes('400: Bad Request. Invalid content type', 'utf-8'))
        else:
            self.send_response(404)
            self.end_headers()
            self.wfile.write(bytes('404: not found', 'utf-8'))

    # Create a home_page variable that contains the HTML for the home page.
    home_page = """
        <html>
        <head>
            <title> File Upload </title>
        </head>
        <body>
            <h1> File Upload </h1>
            <form action="molecule" enctype="multipart/form-data" method="post">
                <p>
                    <input type="file" id="sdf_file" name="filename"/>
                </p>
                <p>
                    <input type="submit" value="Upload"/>
                </p>
            </form>
        </body>
        """
# Create a server that listens on port in command line (57811).
httpd = HTTPServer(('localhost', int(sys.argv[1])), MyHandler)
httpd.serve_forever();
