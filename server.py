from flask import Flask, render_template, jsonify, request
import prprpr as pr

app = Flask(__name__)

@app.route("/")
def index():
    return render_template('paint.html')

@app.route('/pixels', methods=['GET', 'POST'])
def get_pixels():
    if request.method == 'GET':
        return 'oki'

    data = request.get_json()

    if data.get('clear'):
        p = (255, 0, 0)
    else:
        state = data['state']
        index = data['index']
        p = pr.convert_pixelData(index, state)

    

    print(p)
    print("Sending:", p)
    pr.packetSerial(p)
    
    #print(state, index)

    return jsonify({'status': 'ok'})