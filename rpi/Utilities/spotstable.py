
import numpy as np
from copy import deepcopy

#Credits: Adapted from Locality Sensitive Hashing for Similar Item Search by Santhosh Hari
#Linke : https://towardsdatascience.com/locality-sensitive-hashing-for-music-search-f2f1940ace23

class SpotsTable():

    def __init__(self, dims, hash_len, dict = {}):
        self.hash_len = hash_len
        self.dims = dims
        self.table = {}
        self.projections = np.random.randn(self.hash_len, dims)

        if dict:
            for k, v in dict.items():
                self.__setitem__(k, v)




    def _generate_hash(self, vector):
        code = (np.dot(vector, self.projections.T) > 0).astype('int').squeeze()
        return ''.join(code.astype('str'))

    def get(self, vector):
        return self.__getitem__(vector)

    def __getitem__(self, vector):
        code = self._generate_hash(vector)
        return self.table.get(code, [])

    def __setitem__(self, key, value):
        code = self._generate_hash(key)
        self.table[code] = value

    def __iter__(self):
        return iter(self.table.items())

    def __len__(self):
        return len(self.table)





