"""
    通过attrgetter 和 sorted 进行排序
"""
from operator import attrgetter


class User(object):
    """docstring for User"""
    def __init__(self, user_id):
        self.user_id = user_id

    def __repr__(self):
        return 'User({0})'.format(self.user_id)


def sort_notcompare():
    users = [User(1), User(-1), User(10)]
    print(users)
    print(sorted(users, key=lambda u: u.user_id))


def sort_by_attrgetter():
    users = [User(1), User(-1), User(10)]
    print(users)
    print(sorted(users, key=attrgetter('user_id')))


sort_by_attrgetter()
