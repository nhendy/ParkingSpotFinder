from app import app, db
from app.models import *
import os

num_vacant_spots = 0

@app.shell_context_processor
def make_shell_context():
    return {'db': db, 'User': User}

if __name__ == "__main__":
    app.run(host='localhost', port='5000', threaded=True)