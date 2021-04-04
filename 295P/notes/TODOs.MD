- [ ] use multip processing for better performance.
- [ ] use GPU for the processing.
- [ ] MISD for fault tolerance.
- [ ] explore blockchain architecture(crypto currency) or p2p architecture to implement both in 230P and 295P. 
    - [ ] P2P: Napster to BitCoin 
- [ ] 230P will use hadoop so see how to use hadoop here too.
- [ ] watch 3rd lecture.


whats to do?
whats the preference of 295P how to match the 230P?

- timelines and deadlines

- friday 230P 

- go through the 230P requirements and slides.

230P friday extra session.

how to get started.



- 295 hater discussion.
    - 230P which part.
        - projects topics.

- why can't we use the both.
    - the larger the l = 2 paths the lesser likely so can't we just the inverse of it.
        - CRS does and it fails.
    - or use in combination.
    - the doesn't it mean we can test for odd length paths.

    - doesn't the interaction of protein depend more on the physical structure.
        - if its symmetric then the l2 is good.

- sge: Sun Grid Engine - a facility  for  executing  UNIX  jobs  on
     remote machines
    - qstat
    - http://gridscheduler.sourceforge.net/htmlman/manuals.html
    - http://bioinformatics.mdc-berlin.de/intro2UnixandSGE/sun_grid_engine_for_beginners/README.html

- twitter advances search: https://twitter.com/search-advanced?lang=en
- https://prowebscraper.com/blog/best-programming-language-for-web-scraping/
- http://www.diva-portal.org/smash/get/diva2:1415998/FULLTEXT01.pdf
- Nodejs: https://www.digitalocean.com/community/tutorials/how-to-scrape-a-website-with-node-js


- we need web scraping: https://parsers.me/what-is-the-differences-between-web-crawling-and-web-scraping/#:~:text=Unlike%20web%20crawling%2C%20a%20web,or%20to%20create%20something%20new.&text=Web%20crawling%20would%20be%20generally%20what%20Google%2C%20Yahoo%2C%20Bing%20etc.
- https://www.scrapehero.com/open-source-web-scraping-frameworks-and-tools/

- https://hackernoon.com/why-the-world-needs-a-universal-web-scraping-library-for-javascript-21c6b3390e02

- http://books.toscrape.com/

- https://prowebscraper.com/blog/50-best-open-source-web-crawlers/

- https://github.com/BruceDone/awesome-crawler

---
scraper vs api
- https://developer.twitter.com/en/docs/tutorials/how-to-analyze-the-sentiment-of-your-own-tweets


- does the even the hater index is corresponding to the historical data
- do we neeed to match it or not.
- what are the sources for the brand sentiment sources.
    - social media
    - blogs etc.
- how to scrape web scraping vs api
    - web scraping
        - scrapy allowed or not.

- pydoop hadoop api
- hadoop aws


- research analysys.
    - stop words: bag of words: freq weightage.


- SSHFS: remote mount the all your stocks data in the openlabs.
    - validate data: 
    ```
    for each in `ll | awk '{print $9}'`; do echo -e $each; ls $each | wc -w; done
    ```
    - how to do?
    - do you need and empty.
- or on GSC63.complab.uci.edu: https://remoteaccess.labstats.com/university-of-california-irvine.html 

---

source ~/keystone/venvs/tutorials/bin/activate
~/keystone/run.sh 2006 ~/tmp_dir

- this week we wanted to focus on shipping our whole solution for 2006 at least to the point where evaluator like yourself or saad would be able to run our solution as intended like

cd ~/stocks/2006/10
~/keystone/run.sh 2006 ~/tmp_dir | adversary 2006/11

- remove hard coded everything
- use tmp_dir path for our files etc.
- setup the whole environment on openlab
- make the stocks data available on openlab
- combine f-g-magic industry

- as this was for demo this profit is less, the full run on 2006 with our algo yeilds
- show the fg_magic_score.txt
- show the final_results/2006-trades.txt

adversary 2006/11 /home/vbharot/keystone/tmp/final_results/2006-trades.txt

- setup hadoop  
    - local configuration
    - bypass hadoop

- next is 2011 and 2001 handling
- next we will work on the volume of the stocks to buy
- and parallelization
- and adversary
    
---
**FINAL TASKS**

*MUST*
- use du -h to make sure that we are scraping every company
- MAKE PIP FILES AND TEST ON FRESH ENV LIKE AWS
- TEST ON THE RESTRICTED ACCESS TO CHECK IF NOT WRITING ANYTHING
    - LIKE SCRAPY WRITING ANYTHING IN RUN_DIR
- ~~aggregate for 2011~~
- create final minimal code
- reject and give warning for 2001 and 2016 for insufficient data
- handle missing args or incorrect args
- compare and give results in comparison to industry average
- f4 is always 1
- try with diffe delta
    ```
    >>> (quarterly_net_income[0] + quarterly_net_income[1])/(quarterly_total_assets[0] + quarterly_total_assets[1])
    0.048337481992731086
    >>> (quarterly_net_income[2] + quarterly_net_income[3])/(quarterly_total_assets[2] + quarterly_total_assets[3])
    0.04472171265279876
    ```
- REPLACEMENTS FOR MISSING FIELDS
    - ~~ replace long term debt by total liabilities as ~~
    
- [x] ~~handle moths dir instead of names~~

- ~~do we leave out all the companies with '.' in symbol. yes~~
- ~~to estimate the daily cash volume we use first day of month and trade on second based on it~~

*GOOD TO HAVE*
- THINLY TRADED CHECK for HEAVILY TRADED CHECK for f, g score
- for stocks like TEX what f or g factor is misbehaving
- why good stocks like tex are not picked
- why bad ones are picked.
    - https://www.fool.com/investing/international/2007/01/04/the-bestperforming-large-caps-of-2006.aspx

- performance
    - benchmarking all data year data sets
        - 2001 all profiles 6 minutes. (6:26.48)
    - multiprocessing & parallelization

- include investors average.

- Cash volume: in order to use the bid/ask price that's observed in my files,  good rule of thumb is to limit the number of shares you want to buy/sell to no more than about 0.1% of the daily volume. So if you have $100,000 total to spend and you're going to buy 10 companies, you're buying $10k worth for each company; you should restrict your purchases to companies that have a daily cash volume of $1,000,000 or more

*QUERIES*
- how to test on restricted env can saad help?
    - like we are not writing on our own but stuff like __pycache__ might do.
---
**LEARNINGS & FURTHER EXPLORATION**
- use qtrly reve growth and industry average to add more paramter
- excuded . regex
    - symbol": ".*[a-z]\.
    - \..[A-Z]*\t0
- async keyword python
- how'd you use classes here if applicable
- how'd you use decrorators here if applicable
- itmes: https://towardsdatascience.com/a-minimalist-end-to-end-scrapy-tutorial-part-ii-b917509b73f7
    - experimented with the items pipelines.
    - seperation of concerp paradigm.
        - faster modifiability
        - add pre post processing
        - prefereed structure to save info in files. "export file".
        - db preferrably.
        - we don't want to create a csv
            - creating code to handle csv
            - large data may need to be kept in memory, which data can handle
            - much more from link above.
- stocks movement: https://www.youtube.com/watch?v=R3zVC7mFzDA
- http://blog.ditullio.fr/2015/12/24/hadoop-basics-filter-aggregate-sort-mapreduce/

- pydoop & hadoop for future reference:
    - hadoop fs -rm -r /wordcount/output_pydoop && pydoop script script.py /wordcount/input/ /wordcount/output_pydoop
    - hadoop fs -cat /wordcount/output_pydoop/part-r-00000
    - file:///C:/Users/asus/Downloads/Pydoop_a_Python_MapReduce_and_HDFS_API_for_Hadoop.pdf
    - https://gist.github.com/alexwoolford/996f186c539f05ce1589

- F score: https://en.wikipedia.org/wiki/Piotroski_F-score
- G score: https://papers.ssrn.com/sol3/papers.cfm?abstract_id=403180

- what to do with missing data when evaluating not saving?
    - why it is missing?
    - how it will impact our outcomes?
    - https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3668100/
    - MCAR, MAR, MNAR
    - regression(preferred)/multiple imputation, even if its possible because other variables may or may not be enough.
    - pair wise deletion with whatever strategy we use.
    - Mean substitution, Pairwise deletion, listwise deletion, Maximum likelihood estimation (MLE).
    - compeletly missing then remove.

- commands
    ```
    chmod +x run.sh

    sshfs -o IdentityFile=~/.ssh/vnt_openlab_uci allow_other,default_permissions,idmap=user vbharot@openlab.ics.uci.edu:/home/vbharot/stocks /mnt/e/vnt/UCI/stocks


    sshfs -o IdentityFile=~/.ssh/vnt_openlab_uci allow_other,default_permissions,idmap=user vbharot@openlab.ics.uci.edu:/home/vbharot/stocks ./test_mnt


    ./run.sh 2006 ~/tmp_dir
    adversary 2006/11 /home/vbharot/keystone/tmp/final_results/2006-trades.txt



    source ~/keystone/venvs/tutorials/bin/activate
    cd ~/stocks/2006/10
    <!-- ~/keystone/run.sh 2006 ~/tmp_dir -->
    ~/keystone/run.sh 2006 ~/tmp_dir | adversary 2006/11
    adversary 2006/11 /home/vbharot/keystone/tmp/final_results/2006-trades.txt
    ```
```
SAVE_PATH=~/tmp_dir/results_2006_12_20_limit.txt
python trade.py 2006 11 12 ~/tmp_dir/ ~/stocks/ > $SAVE_PATH && adversary $SAVE_PATH >> $SAVE_PATH
```

- scrape progress
```
wc -l ~/tmp_dir/stocks_data_20*
```

- to scrap .html
```
echo $((`find . -name "*.html" | wc -l`-`find . -name "*.*.html" | wc -l`))
```