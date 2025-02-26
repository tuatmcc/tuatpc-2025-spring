import requests
import json
from problem import Problem
import re

API_URL = 'https://api.mofecoder.com/api'
LOGIN_URL = 'https://api.mofecoder.com/api/auth/sign_in'

class Client:
    def __init__(self):
        self.logined = False
        self.headers = None

    def login(self, username: str, password: str) -> int:
        data = {
            'name': username,
            'password': password
        }
        try:
            response = requests.post(LOGIN_URL, data=data)
            response.raise_for_status()
            self.logined = True
            self.headers = {
                'client': response.headers['client'],
                'Authorization': response.headers['Authorization'],
                'uid': response.headers['uid'],
                'access-token': response.headers['access-token']
            }
        except requests.exceptions.RequestException as e:
            print(f'Login failed: {e}')
            return response.status_code if response else 500
        return response.status_code

    def _request(self, method: str, url: str, headers={}, **kwargs):
        if not self.logined:
            print('Not logged in')
            return None
        try:
            response = requests.request(method, API_URL + url, headers=self.headers | headers, **kwargs)
            response.raise_for_status()
            return response
        except requests.exceptions.RequestException as e:
            print(f'Request failed: {e}')
            return None

    def get_problem(self, problem_id: int) -> Problem:
        response = self._request('GET', f'/problems/{problem_id}')
        return Problem.from_dict(response.json())

    def get_testcases(self, problem_id: int):
        response = self._request('GET', f'/problems/{problem_id}/testcases')
        return response.json()
    
    def get_testcase(self, problem_id: int, testcase_id: int):
        response = self._request('GET', f'/problems/{problem_id}/testcases/{testcase_id}')
        return response.json()
    
    def delete_multiple_testcases(self, problem_id: int, testcase_ids: list[int]) -> int:
        payload = json.dumps({'testcases': testcase_ids})
        headers = {'content-type': 'application/json', 'content-length': str(len(payload))}
        response = self._request('DELETE', f'/problems/{problem_id}/testcases/delete_multiple', headers=headers, data=payload)
        return response.status_code if response else 500

    def upload_testcases(self, problem_id: int, filename: str, delete_old_testcases: bool = True) -> int:
        if delete_old_testcases:
            try:
                testcases = self.get_testcases(problem_id)
                testcase_ids = [testcase['id'] for testcase in testcases['testcases']]
                self.delete_multiple_testcases(problem_id, testcase_ids)
            except Exception as e:
                print(f'Error deleting old testcases: {e}')
        with open(filename, 'rb') as f:
            response = self._request('POST', f'/problems/{problem_id}/testcases/upload', files={'file': f})
            return response.status_code if response else 500

    def get_testcase_ids(self, problem_id: int, regex_ptrn:re.Pattern):
        testcases = self.get_testcases(problem_id)
        return [testcase['id'] for testcase in testcases['testcases'] if regex_ptrn.match(testcase['name'])]

    def get_testcase_set_id_by_name(self, problem_id: int, testcase_set_name: str):
        testcase_sets = self.get_testcases(problem_id)['testcase_sets']
        for testcase_set in testcase_sets:
            if testcase_set['name'] == testcase_set_name:
                return testcase_set['id']
        return None

    def testcases_change_state_multiple(self, problem_id: int, testcase_ids: list[int], testcase_set_id: int) -> int:
        response = self._request('PUT', f'/problems/{problem_id}/testcases/change_state_multiple',
                      data={'testcase_ids': testcase_ids, 'testcase_set_id': testcase_set_id})
        return response.status_code if response else 500

    def post_testcase_sets(self, problem_id: int, testcase_sets: dict[str, str]) -> int:
        if 'aggregate_type' not in testcase_sets:
            testcase_sets['aggregate_type'] = 'all'
        payload = json.dumps(testcase_sets, ensure_ascii=False)
        headers = {'content-type': 'application/json', 'content-length': str(len(payload))}
        response = self._request('POST', f'/problems/{problem_id}/testcase_sets', headers=headers, data=payload)
        return response.status_code if response else 500

    def put_problem(self, problem_id: int, problem: Problem) -> int:
        payload = json.dumps(problem.to_dict(), ensure_ascii=False)
        headers = {'content-type': 'application/json', 'content-length': str(len(payload))}
        response = self._request('PUT', f'/problems/{problem_id}', headers=headers, data=payload)
        return response.status_code if response else 500
