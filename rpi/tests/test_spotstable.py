import unittest
import os
import sys
import json
import random
import shutil

root = os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir, os.path.pardir))
sys.path.append(root)

from rpi.Utilities.spotstable import SpotsTable



class TestSpotsTable(unittest.TestCase):

    _actual_centers_to_ids = {}
    _faulty_centers_to_ids = {}
    _ids_to_actual_centers = {}

    @classmethod
    def setUpClass(cls):
        super(TestSpotsTable, cls).setUpClass()

        with open(os.path.join(root, 'rpi/tests/fixtures/lookup.json'), 'r') as file:
            TestSpotsTable._actual_centers_to_ids = { eval(k) : v for k, v in json.load(file).items()}


        for coords, id in TestSpotsTable._actual_centers_to_ids.items():
            TestSpotsTable._ids_to_actual_centers[id] = coords



    @staticmethod
    def add_error(percent, both = False):

        for coords, id in TestSpotsTable._actual_centers_to_ids.items():
            new_coords = list(coords)
            if not both:
                new_coords[random.choice([0, 1])] +=  percent * \
                                                      new_coords[random.choice([0, 1])] * random.choice([1 , -1])
            else:
                new_coords[0] += percent * new_coords[0] * random.choice([1, -1])
                new_coords[1] += percent * new_coords[1] * random.choice([1, -1])

            TestSpotsTable._faulty_centers_to_ids[tuple(new_coords)] = id





    def test_(self):

        #add  error percentage
        TestSpotsTable.add_error(0.04)
        lookup_table = SpotsTable(dict=TestSpotsTable._actual_centers_to_ids)

        num_failures = 0
        for coords, expected_id in TestSpotsTable._faulty_centers_to_ids.items():
            actual_id = lookup_table.get(coords)
            if expected_id != actual_id:
                num_failures += 1
                print("{!r:>10}'s id didn't match  {!r:>10}'s id it matched  "
                      "{!r:>10}".format(coords, TestSpotsTable._ids_to_actual_centers[expected_id],
                                  TestSpotsTable._ids_to_actual_centers[actual_id]))

        print("\n\n\n{:=^{width}}\n\n\n".format( ' {}/{} FAILED '.format(num_failures,
                                                                         len(TestSpotsTable._faulty_centers_to_ids)),
                                                 width = shutil.get_terminal_size().columns ))

    # def setUp(self):
    #    '''
    #    Creates the test vectors required for the test functions below.
    #
    #    '''



if __name__ == '__main__':
    unittest.main()

