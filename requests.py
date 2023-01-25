import requests as req

url = 'http://www.golfportal.si/'
response = req.get(url)

if response.status_code == 200:
    print(response.text)
else:
    print(f'Error accessing website. Status code: {response.status_code}')
