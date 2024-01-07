import os
from datetime import datetime, timedelta
from flask import Flask, abort, request
from mysql import Mysql
from logger import log

app = Flask(__name__)
mySql = Mysql()

ESP_API_TOKEN = os.getenv('ESP_API_TOKEN')

@app.route('/esp', methods=['POST'])
def esp():
    log.info('Run /esp')

    buff = request.data.decode('utf-8')
    log.debug(buff)

    lines = buff.split('\n')
    delta = len(lines)
    for iter in range(delta):
        time = datetime.now() - timedelta(minutes = iter)
        lines[delta - iter - 1] = lines[delta - iter - 1].replace('{', '{\"date\": \"' +  str(time) +  '\", ')
        print(lines[delta - iter - 1])

    if 'token' not in request.headers:
        log.error('No header')
        abort(417)
    elif request.headers['token'] != ESP_API_TOKEN:
        log.error('Invalid token: ' + request.headers['token'])
        abort(401)
    else:
        log.info('Insert data to DB')
        for line in lines:
            print(line)
            if not mySql.tryToInsert(eval(line)):
                log.error('Database error')
                abort(422)
    return "xD"

@app.route('/result', methods=['GET'])
def result():
    abort(404)

@app.route('/health', methods=['GET'])
def health():
    log.info('Checking /health')

    result = mySql.tryToSelect()
    result = result.one()

    return str(result)

@app.route('/')
def main():
    log.warn('Someone is comming')
    return 'Hell!'
