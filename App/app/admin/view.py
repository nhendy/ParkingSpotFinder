from flask_admin.contrib import sqla
from  flask_security import current_user
from flask import redirect, url_for


class AdminView(sqla.ModelView):
    pass
    # def is_accessible(self):
    #     user = User.query.filter_by(username=current_user.name).first()
    #     return user.roles == 'Admin'
    #
    # def inaccessible_callback(self, name, **kwargs):
    #     return redirect(url_for('auth.login'))