from app import db, login
from sqlalchemy.dialects.postgresql import JSON
from flask_login import UserMixin
from werkzeug.security import generate_password_hash, check_password_hash
from datetime import datetime



class User(UserMixin, db.Model):
    __tablename__ = 'Users'
    id             = db.Column(db.Integer,primary_key=True)
    username       = db.Column(db.String(250), nullable=False, unique=True)
    password_hash  = db.Column(db.String(250), nullable=False)
    reserved       = db.Column(db.Boolean, nullable=False, default=False)
    timestamp      = db.Column(db.DateTime, nullable=False, default=datetime.utcnow)


    def __init__(self, username):
        self.username = username

    def __repr__(self):
        return '<id {}, username {}>'.format(self.id, self.username)

    def set_password(self, password):
        self.password_hash = generate_password_hash(password)

    def check_password(self, password):
        return check_password_hash(self.password_hash, password)



@login.user_loader
def load_user(id):
    return User.query.get(int(id))
