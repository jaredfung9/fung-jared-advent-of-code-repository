import unittest, os
import day_2

def open_file(name):
    cwd = os.path.dirname(__file__)
    test_dir = os.path.join(cwd, "unittests/")
    return open(os.path.join(test_dir, name), "r")

class TestReportCountMethods(unittest.TestCase):

    def test_incr(self):
        file = open_file("all_increasing.txt")
        self.assertEqual(day_2.count_safe_reports(file), 1)
        file.close()

    def test_decr(self):
        file = open_file("all_decreasing.txt")
        self.assertEqual(day_2.count_safe_reports(file), 1)
        file.close()

    def test_bad_decr(self):
        file = open_file("bad_decreasing_difference.txt")
        self.assertEqual(day_2.count_safe_reports(file), 0)
        file.close()

    def test_bad_incr(self):
        file = open_file("bad_increasing_difference.txt")
        self.assertEqual(day_2.count_safe_reports(file), 0)
        file.close()

    def test_various_size(self):
        file = open_file("various_size.txt")
        self.assertEqual(day_2.count_safe_reports(file), 3)
        file.close()

    def test_bad_various_size(self):
        file = open_file("bad_various_size.txt")
        self.assertEqual(day_2.count_safe_reports(file), 3)
        file.close()

    def test_twos(self):
        file = open_file("twos.txt")
        self.assertEqual(day_2.count_safe_reports(file), 2)
        file.close()
    
    def test_threes(self):
        file = open_file("threes.txt")
        self.assertEqual(day_2.count_safe_reports(file), 3)
        file.close()

    def test_fours(self):
        file = open_file("fours.txt")
        self.assertEqual(day_2.count_safe_reports(file), 0)
        file.close()
    
    def test_mixed_increasing(self):
        file = open_file("mixed_increasing.txt")
        self.assertEqual(day_2.count_safe_reports(file), 1)
        file.close()

    def test_mixed_decreasing(self):
        file = open_file("mixed_decreasing.txt")
        self.assertEqual(day_2.count_safe_reports(file), 3)
        file.close()

    def test_problem_dampener_demo(self):
        file = open_file("demo_input_2.txt")
        self.assertEqual(day_2.count_safe_reports(file, True), 4)
        file.close()

    def test_demo(self):
        file = open_file("demo_input_2.txt")
        self.assertEqual(day_2.count_safe_reports(file), 2)
        file.close()

    def test_tricky_dampener(self):
        file = open_file("tricky_dampener.txt")
        self.assertEqual(day_2.count_safe_reports(file, True), 10)
        file.close()

if __name__ == '__main__':
    unittest.main()