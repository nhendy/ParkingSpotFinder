import os
import requests
from flask import Flask
from flask import current_app, g
import sqlite3


app = Flask(__name__, instance_relative_config=True)
app.config.from_mapping(
    SECRET_KEY='dev',
    DATABASE=os.path.join(app.instance_path, 'flaskr.sqlite'),
)

# ensure the instance folder exists
try:
    os.makedirs(app.instance_path)
except OSError:
    pass

# a simple page that says hello
@app.route('/hello')
def hello():
    return 'Hello, team 18!'

@app.route('/parkme')
def parkme():
    return "parkme"
#
# print(os.getcwd())

# from . import db
# init_db()

# app.add_url_rule('/', endpoint='index')


def connect_db():
    """Connects to the database."""
    rv = sqlite3.connect(app.config['DATABASE'])
    rv.row_factory = sqlite3.Row
    return rv


# create the database
def init_db():
    with app.app_context():
        db = get_db()
        with app.open_resource('schema.sql', mode='r') as f:
            db.cursor().executescript(f.read())
        db.commit()


# open database connection
def get_db():
    if not hasattr(g, 'sqlite_db'):
        g.sqlite_db = connect_db()
    return g.sqlite_db


# close database connection
@app.teardown_appcontext
def close_db(error):
    if hasattr(g, 'sqlite_db'):
        g.sqlite_db.close()


def create_app(test_config=None):

    import auth
    app.register_blueprint(auth.bp)

    import blog
    app.register_blueprint(blog.bp)

    init_db()

    return app


if __name__ == "__main__":
    import auth, blog
    app.register_blueprint(auth.bp)
    app.register_blueprint(blog.bp)
    init_db()
    app.run()
