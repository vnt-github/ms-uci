#!/usr/bin/env python
# coding: utf-8

'''
pip install imap_tools lxml
apt install libxslt-dev
'''


# read
from imap_tools import MailBox, AND
from lxml import html
from urllib.parse import unquote

# reply
import smtplib
from getpass import getpass
from email.mime.text import MIMEText

# automate
from os import system, path, mkdir, getenv
from shutil import copyfile
from platform import system as sys
sys = sys()
home = getenv('HOME')


# info
receiver = 'uci@service-now.com'
sender = 'UCInetID@uci.edu'
password = 'password'
subject = 'UCI Student Daily Symptom Monitoring'
content = ''


# check if first run
run = not path.exists(home+'/uci_covid_email/uci_reply.py')


with MailBox('imap.gmail.com').login(sender, password, 'INBOX') as mailbox:
    for msg in mailbox.fetch(AND(seen=False, subject=subject)):
        for a in html.fromstring(msg.html).findall('.//a'):
            if a.text == 'Not on campus today':
                # decode subject and body from link
                subject = unquote(a.get('href').split(
                    '?')[1].split('=')[1].split('&')[0]).strip()
                content = unquote(a.get('href').split(
                    '?')[1].split('=')[2].split('&')[0]).strip()

                msg = MIMEText(content)
                msg['From'] = sender
                msg['To'] = receiver
                msg['Subject'] = subject

                server = smtplib.SMTP_SSL('smtp.gmail.com:465')
                server.login(sender, password)
                # send reply
                server.send_message(msg)
                server.quit()


# automatically reply to emails
if run:
    mkdir(home+'/uci_covid_email/')
    copyfile('uci_reply.py', home+'/uci_covid_email/uci_reply.py')
    if sys == 'Darwin' or sys == 'Linux':
        system('crontab -l | { cat; echo "0 */2 * * * cd '+home +
               '/uci_covid_reply/ && $(which python3) '+home+'/uci_covid_reply/uci_reply.py"; } | crontab -')
    elif sys == 'Windows':
        system('schtasks /create /sc hourly /mo 2 /tn "UCI Covid Reply" /tr python3.exe ' +
               home+'/uci_covid_email/uci_reply.py')