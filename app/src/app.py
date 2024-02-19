import os
from datetime import datetime, timedelta
from flask import Flask, abort, request
from mysql import Mysql
from logger import log
import json

app = Flask(__name__)

ESP_API_TOKEN = os.getenv('ESP_API_TOKEN')

@app.route('/esp', methods=['POST'])
def esp():
    log.info('Run /esp')

    mySql = Mysql()
    buff = request.data.decode('utf-8')
    log.debug(buff)

    if 'token' not in request.headers:
        log.error('No header')
        abort(417)
    elif request.headers['token'] != ESP_API_TOKEN:
        log.error('Invalid token: ' + request.headers['token'])
        abort(401)
    else:
        log.info('Add timestamp')
        lines = buff.split('\n')
        delta = len(lines)
        time = datetime.now() + timedelta(hours = 1)
        for iter in range(delta):
            if iter and not iter % 2:
                time = time - timedelta(minutes = 1)
            lines[delta - iter - 1] = lines[delta - iter - 1].replace('{', '{\"date\": \"' +  str(time) +  '\", ')

        log.info('Insert data to DB')
        for line in lines:
            log.debug(line)
            if not mySql.tryToInsert(json.loads(line)):
                log.error('Database error')
                abort(422)
    return "xD"

@app.route('/result', methods=['GET'])
def result():
    log.info('Checking /result')

    mySql = Mysql()
    result = mySql.tryToSelect('SELECT * FROM MEASUREMENT WHERE ID IN (SELECT MAX(ID) FROM MEASUREMENT)')
    result = result.one()

    return str(result)

@app.route('/health', methods=['GET'])
def health():
    log.info('Checking /health')

    mySql = Mysql()
    result = mySql.tryToSelect()
    result = result.one()

    return str(result)

@app.route('/')
def main():
    log.warn('Someone is comming')
    return 'Hell!'
