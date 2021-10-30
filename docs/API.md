
## API USAGE JWSESP

### Restart ESP ( GET )
```
/api/restart
```
+ usage : http://192.168.4.1/api/restart

### Get Location Config ( GET )
```
/api/prayerconfig.json
```
+ usage : http://192.168.4.1/api/prayerconfig.json

### Get Settings Config ( GET )
```
/api/settingsconfig.json
```
+ usage : http://192.168.4.1/api/settingsconfig.json

### Get Prayer Fix Config ( GET )
```
/api/prayercompare.json
```
+ usage : http://192.168.4.1/api/prayercompare.json


### Get Info Config ( GET )
```
/api/infoconfig.json
```
+ usage : http://192.168.4.1/api/infoconfig.json

### Login ( POST )
```
/api/login
```
+ usage : http://192.168.4.1/api/login
+ params : username, password

### Set Time ( POST )
```
/api/set_time
```
+ usage    : http://192.168.4.1/api/set_time
+ params  :
	- second
	- minute
	- hour
	- day
	- month
	- year

### Set Location ( POST )
```
/api/set_prayer_config
```
+ usage    : http://192.168.4.1/api/set_prayer_config
+ params  :
	- latitude (float)
	- longitude (float)
	- timezone (int)
	- fajr_angle (int)
	- isha_angle (int)
info : if any of the params is not available, it will be set to default

### Set Prayer Fix ( POST )
```
/api/set_prayer_comparation
```
+ usage    : http://192.168.4.1/api/set_prayer_comparation
+ params  :
	- imsak
	- shubuh
	- terbit
	- dzuhur
	- ashar
	- terbenam
	- maghrib
	- isya
+ info :
	- if any of the params is not available, it will be set to default
	- ( - ) to reduce per minute, ( + ) to add a minute

### Set Settings ( POST )
```
/api/set_settings
```
+ usage    : http://192.168.4.1/api/set_settings
+ params  :
	- wifi_name
	- wifi_password
	- login_username
	- login_password
	- brightness (int)
	- marque_speed (int)

### Set Info ( POST )
```
/api/set_info
```
+ usage    : http://192.168.4.1/api/set_info
+ params  :
	- show_mosque_name  (0 to false, 1 to true)
	- show_info_1  (0 to false, 1 to true)
	- show_info_2  (0 to false, 1 to true)
	- show_info_3  (0 to false, 1 to true)
	- mosque_name
	- info_1
	- info_2
	- info_3