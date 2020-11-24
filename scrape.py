import requests
from bs4 import BeautifulSoup


url = "https://www-cs-faculty.stanford.edu/~knuth/programs.html"
req = requests.get(url)
soup = BeautifulSoup(req.content, 'html.parser')


links = soup.find_all("a")

prefix = "https://www-cs-faculty.stanford.edu/~knuth/programs/"

for link in links:
    try:
        link = link.get("href")
        if link.split(".")[-1] == "w":
            name = link.split("/")[-1]
            #print(prefix+name)
            content = requests.get(prefix + name).content.decode()
            with open( "programs/" + name, "w" ) as f:
                f.write( requests.get(prefix + name).content.decode())
                
    except Exception as e:
        print(e)