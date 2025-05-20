import datetime
import configparser
import requests
import json
import re


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

counter = Counter()

config = configparser.ConfigParser()
config.read('config.conf')

domain = config.get('JIRA', 'DOMAIN')
email = config.get('JIRA', 'EMAIl')
api_token = config.get('JIRA', 'API_TOKEN')

jql = config.get('JIRA', 'JQL')
field = config.get('JIRA', 'FIELD')
field_value = config.get('JIRA', 'FIELD_VALUE')
url = f"https://{domain}/rest/api/latest/search"

auth = (email, api_token)
headers = {
        "Accept": "application/json"
}

params = {
        "jql": jql,
        "fields": field,
        "maxResults": 10
}

response = requests.get(url, headers=headers, params=params, auth=auth)

if response.status_code == 200:
    issues = response.json().get("issues", [])
    for issue in issues:
        match = re.search(field_value, json.dumps(issue.get("fields").get(field)))
        if match:
            print("Found match. Resetting counter...")
            counter.reset()
else:
    print("Error:", response.status_code)
    print(response.text)
