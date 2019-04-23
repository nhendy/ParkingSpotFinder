import requests
from requests.auth import HTTPBasicAuth
import json

def send_request():
    vacant_spot_count = 10
    code = "12345"
    #if you want a count of number of reservations
    response = request_reserved_spot_count(vacant_spot_count)
    #if you want to validate code
    response = validate_code(code, vacant_spot_count)
    return response

def request_reserved_spot_count(vacant_spot_count):
    my_data = {
        "request_for_reserved_spots": "True",
        "code_generated": "",
        "vacant_spot_count": str(vacant_spot_count)
    }
    r = requests.post('http://127.0.0.1:5000/pi_to_app',
                      json=my_data,
                      auth=HTTPBasicAuth('username', '1234'))
    return r

def validate_code(code, vacant_spot_count):
    my_data = {
        "request_for_reserved_spots": "False",
        "code_generated": code,
        "vacant_spot_count": str(vacant_spot_count)
    }
    r = requests.post('http://127.0.0.1:5000/pi_to_app',
                      json=my_data,
                      auth=HTTPBasicAuth('username', '1234'))
    return r