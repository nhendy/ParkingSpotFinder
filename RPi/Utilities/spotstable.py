
import numpy as np
from copy import deepcopy
from pprint import pprint
import os
import json

class SpotsTable():
    def __init__(self, file=None, dict=None):
        self.table = {}

        if file is not None:
            if dict is not None:
                raise ValueError('Can only provide dict or file, not both')

            _, ext = os.path.splitext(file)
            if ext.strip('.') != 'json':
                raise ValueError('File must be in JSON format.')

            with open(os.path.abspath(file), 'r') as file:
                self.table =  {eval(k): v for k, v in json.load(file).items()}

        else:
            self.table = deepcopy(dict)


    def get(self, vector):
        return self.__getitem__(vector)

    def _find_nearest_neighbor(self, vector):
        min_distance = float('Inf')
        result = None
        for k in self.table.keys():
            distance = np.linalg.norm(np.asarray(k) - np.asarray(vector))
            if distance < min_distance:
                min_distance = distance
                result = k
        return result



    def __getitem__(self, vector):
        key = self._find_nearest_neighbor(vector)
        return self.table.get(key)

    def __setitem__(self, key, value):
        self.table[key] = value

    def __iter__(self):
        return iter(self.table)

    def __len__(self):
        return len(self.table)



#Credits: Adapted from Locality Sensitive Hashing for Similar Item Search by Santhosh Hari
#Linke : https://towardsdatascience.com/locality-sensitive-hashing-for-music-search-f2f1940ace23

# class SpotsTable():
#
#     def __init__(self, num_tables, hash_len, dims, dict={}):
#         self.num_tables = num_tables
#         self.hash_len = hash_len
#         self.dims = dims
#         self.storage = deepcopy(dict)
#         self.hash_tables = []
#         for i in range(self.num_tables):
#             self.hash_tables.append(HashTable(self.dims, self.hash_len))
#
#         for k, v in dict.items():
#             self.__setitem__(k, v)
#
#         pprint(self.storage)
#         pprint(self.hash_tables[0].table)
#
#
#     def __setitem__(self, inp_vec, label):
#         self.storage[inp_vec] = label
#
#         for table in self.hash_tables:
#             table.add(inp_vec)
#
#
#     def l2_norm_criterion(self, query_vec, results):
#         final_vector = None
#         min_distance = float('Inf')
#
#         for result in results:
#             distance = np.linalg.norm(np.asarray(query_vec) - result)
#             if distance < min_distance:
#                 min_distance = distance
#                 final_vector = result
#
#         return final_vector
#
#
#     def cosine_similarity(self, query_vec, results):
#         final_vector = None
#         max_similatiry = float('-Inf')
#
#         for result in results:
#             similarity = np.dot(query_vec, result) / (np.linalg.norm(query_vec) * np.linalg.norm(result))
#             if similarity > max_similatiry:
#                 max_similatiry = similarity
#                 final_vector = result
#
#         return final_vector
#
#     def query (self, inp_vec, criterion = 'L2'):
#         results = list()
#         for table in self.hash_tables:
#             results.append(table.get(inp_vec))
#         pprint(results)
#         if criterion == 'L2':
#             return self.storage[self.l2_norm_criterion(inp_vec, results)]
#
#         return self.storage[self.cosine_similarity(inp_vec, results)]
#
#
#
#
# class HashTable():
#     def __init__(self, dims, hash_len):
#         self.hash_len = hash_len
#         self.dims = dims
#         self.table = {}
#         self.projections = np.random.randn(self.hash_len, dims)
#
#         # if dict:
#         #     for k, v in dict.items():
#         #         self.__setitem__(k, v)
#         print(len(self.projections))
#         print("Project vectors are\n {}".format(self.projections))
#
#
#     def _generate_hash(self, vector):
#         code = (np.dot(vector, self.projections.T) > 0).astype('int').squeeze()
#         return ''.join(code.astype('str'))
#
#     def get(self, vector):
#         return self.__getitem__(vector)
#
#     def __getitem__(self, vector):
#         code = self._generate_hash(vector)
#         return self.table.get(code, [])
#
#     def add (self, key):
#         code = self._generate_hash(key)
#         self.table[code] = self.table.get(code, []) + [key]
#
#     def __iter__(self):
#         return iter(self.table.items())
#
#     def __len__(self):
#         return len(self.table)
#

