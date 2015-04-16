def countDays(dateInString):

    date_time = dateInString.split('.')
    from datetime import datetime
    if len(date_time) == 3:
        try:
            formatted_date = datetime.strptime(date_time[2] + '-' + date_time[0] + '-' + date_time[1], "%Y-%m-%d")
            default_date = datetime.strptime((date_time[2]+ '-01-01'), "%Y-%m-%d")
            diff = (formatted_date - default_date).days
            return diff + 1
        except:
            return "bad format"
    else:
        return "bad format"

print countDays("72.01.2014")