import urllib2
import simplejson

url = ('https://ajax.googleapis.com/ajax/services/search/images?' +
       'v=1.0&q=barack%20obama&userip=INSERT-USER-IP')

request = urllib2.Request(url, None, {'Referer': /* Enter the URL of your site here */})
response = urllib2.urlopen(request)

# Process the JSON string.
results = simplejson.load(response)
# now have some fun with the results...
