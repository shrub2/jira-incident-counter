import datetime
import configparser
import requests


class Counter:
    def __init__(self):
        self.counter = 0
        self.incident_ts = datetime.datetime.now()

    def increment(self):
        self.counter += 1

    def reset(self):
        self.counter = 0
        self.incident_ts = datetime.datetime.now()

        
# End of Counter

config = configparser.ConfigParser()
config.read('config.txt')

domain = config.get('JIRA', 'DOMAIN')
email = config.get('JIRA', 'EMAIl')
api_token = config.get('JIRA', 'API_TOKEN')

jql = config.get('JIRA', 'JQL')
url = f"https://{domain}/rest/api/latest/search"

auth = (email, api_token)
headers = {
        "Accept": "application/json"
}

params = {
        "jql": jql,
        "maxResults": 10
}

response = requests.get(url, headers=headers, params=params, auth=auth)

if response.status_code == 200:
    issues = response.json().get("issues", [])
    for issue in issues:
        key = issue["key"]
        print(key)
else:
    print("Error:", response.status_code)
    print(response.text)
