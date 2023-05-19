import unittest
from selenium import webdriver

class LewisUniversityUAT(unittest.TestCase):

    def setUp(self):
        self.driver = webdriver.Chrome()

    def tearDown(self):
        self.driver.quit()

    def test_title(self):
        self.driver.get("https://www.lewisu.edu/")
        self.assertIn("Lewis University", self.driver.title)

    def test_links(self):
        self.driver.get("https://www.lewisu.edu/")
        links = ["About Us", "Academics", "Admission and Aid", "Athletics", "Student Life", "Locations"]
        for link in links:
            elem = self.driver.find_element_by_link_text(link)
            self.assertIsNotNone(elem)

    def test_faculty_directory(self):
        self.driver.get("https://www.lewisu.edu/")
        faculty_link = self.driver.find_element_by_link_text("Faculty/Staff Directory")
        faculty_link.click()
        self.assertIn("Faculty & Staff Directory", self.driver.title)

    def test_search(self):
        self.driver.get("https://www.lewisu.edu/")
        search_box = self.driver.find_element_by_id("s")
        search_box.send_keys("Omari")
        search_box.submit()
        results = self.driver.find_elements_by_class_name("result")
        self.assertGreater(len(results), 0)

if __name__ == '__main__':
    unittest.main()