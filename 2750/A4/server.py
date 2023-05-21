import http.server
import sys
import io
import urllib.parse
import cgi
import molsql
import MolDisplay
import molecule
import json
import urllib;  # code to parse for data


db = molsql.Database(reset=True)
db.create_tables()
db['Elements'] = ( 1, 'H', 'Hydrogen', '#FFFFFF', '#050505', '#020202', 25 );
db['Elements'] = ( 6, 'C', 'Carbon', '#808080', '#010101', '#000000', 40 );
db['Elements'] = ( 7, 'N', 'Nitrogen', '#0000FF', '#000005', '#000002', 40 );
db['Elements'] = ( 8, 'O', 'Oxygen', '#FF0000', '#050000', '#020000', 40 );

public_files = ['/styles.css', '/index.html', '/script.js']
mol = MolDisplay.Molecule()
class MyHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path in public_files:
            self.send_response(200)
            content_type = 'text/plain'
            if self.path.endswith('.html'):
                content_type = 'text/html'
            elif self.path.endswith('.css'):
                content_type = 'text/css'
            else:
                content_type = 'text/plain'
            self.send_header('Content-type', content_type)
            file = open(self.path[1:], 'rb')
            page = file.read()
            self.send_header('Content-length', len(page))
            self.end_headers()
            self.wfile.write(page)
        
        elif self.path == "/":
            #go straight to the index page
            self.send_response(301)
            self.send_header('location', '/index.html')
            self.end_headers()
            self.wfile.write(bytes('Redirecting to index.html', 'utf-8'))
            
        elif self.path == "/view-molecule":
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(bytes('view molecule', 'utf-8'))
            
        elif self.path == "/moleculeDetails":
            molecules = db.get_Molecules()
            json_string = json.dumps(molecules)

            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(bytes(json_string, 'utf-8'))

        elif self.path =="/element-page":
            elements = db.get_Elements();
            json_string = json.dumps(elements)
            
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(bytes(json_string, 'utf-8'))
            
        elif self.path.startswith("/getSVG"):
            query_components = urllib.parse.parse_qs(urllib.parse.urlparse(self.path).query)
            molecule_id = query_components["id"][0]
            MolDisplay.radius = db.radius();
            MolDisplay.element_name = db.element_name();
            MolDisplay.header += db.radial_gradients();
            mol = db.load_mol(molecule_id)
            mol.sort()
            svgString = mol.svg()
            json_svg = json.dumps(svgString)
            self.send_response(200)
            self.send_header('location', '/index.html#view-molecule')
            self.end_headers()
            self.wfile.write(bytes(json_svg, 'utf-8'))

        else:
            self.send_response(404)
            self.end_headers()
            self.wfile.write(bytes('404: not found', 'utf-8'))

    def do_POST(self):

        if self.path == "/uploadSDF":
            content_length = int(self.headers['Content-Length'])
            lines = self.rfile.read(content_length).decode('utf-8')

            name = lines.split("\n", 4)[3]
            name = name.rstrip("\r")
            data = lines.split("\n", 8)[8]
            if db.check_unique_mol(name) is True:
                print("Molecule already exists in table")
                message = "Molecule already exists in table"
                self.send_response(301)
                self.send_header('location', 'index.html')
                self.end_headers()
                return
            else:
                data_stream = io.BytesIO(bytes(data, 'utf-8'))
                data_wrapper = io.TextIOWrapper(data_stream, encoding='utf-8')
                db.add_molecule(name, data_wrapper)
                message = "Molecule already exists in table"
                self.send_response(301)
                self.send_header('location', 'index.html')
                self.end_headers()
                return

        elif self.path == "/element-page":
            content_length = int(self.headers['Content-Length']);
            body = self.rfile.read(content_length).decode('utf-8');
            form_data = urllib.parse.parse_qs(body)
            element_name = form_data.get('element-name')[0]
            element_number = form_data.get('element-number')[0]
            element_code = form_data.get('element-code')[0]
            color1 = form_data.get('color1')[0]
            color2 = form_data.get('color2')[0]
            color3 = form_data.get('color3')[0]
            radius = form_data.get('radius')[0]
            if (db.check_unique_element(element_code) is not True):
                db['Elements'] = ( int(element_number), element_code, element_name, color1, color2, color3, int(radius));
            else:
                print("Element already exists in table")
                # send a message to the js file to display a message to the user
                message = "Element already exists in table"
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(bytes(json.dumps({"message": message}), 'utf-8'))
                return
            self.send_response(200)
            self.send_header('Content-type', 'json/html')
            self.end_headers()
            self.wfile.write(bytes('element page', 'utf-8'))

        elif self.path == "/delete-element":
            content_length = int(self.headers['Content-Length']);
            body = self.rfile.read(content_length).decode('utf-8');
            form_data = urllib.parse.parse_qs(body)
            elementNum = form_data.get('element-code')[0]
            elementName = form_data.get('element-name')[0]
            db.del_Elements(elementName)
            
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(bytes('delete element', 'utf-8'))
            
        elif self.path == "/rotateSVG":
            content_length = int(self.headers['Content-Length']);
            body = self.rfile.read(content_length).decode('utf-8');
            form_data = urllib.parse.parse_qs(body)
            molName = form_data.get('mol-name')[0]
            rotateX = int(form_data.get('rotate-x')[0])
            rotateY = int(form_data.get('rotate-y')[0])
            rotateZ = int (form_data.get('rotate-z')[0])
            mol = db.load_mol(molName)
            mol.sort()
            if (rotateX == 0 and rotateY == 0 and rotateZ == 0):
                rotateSVG = mol.svg()
                self.send_response(200)
                self.send_header('Content-Type', 'text/html')
                self.end_headers()
                self.wfile.write(bytes(rotateSVG, 'utf-8'))
                return
            elif (rotateX == 360 and rotateY == 360 and rotateZ == 360):
                rotateSVG = mol.svg()
                self.send_response(200)
                self.send_header('Content-Type', 'text/html')
                self.end_headers()
                self.wfile.write(bytes(rotateSVG, 'utf-8'))
                return
            
            mx = molecule.mx_wrapper(rotateX, rotateY, rotateZ)
            mol.xform(mx.xform_matrix)
            rotateSVG = mol.svg()
            self.send_response(200)
            self.send_header('Content-Type', 'text/html')
            self.end_headers()
            self.wfile.write(bytes(rotateSVG, 'utf-8'))
            
        else:
            self.send_response(404)
            self.end_headers()
            self.wfile.write(bytes('404: not found', 'utf-8'))


httpd = http.server.HTTPServer(('localhost', int(sys.argv[1])), MyHandler)
httpd.serve_forever()
