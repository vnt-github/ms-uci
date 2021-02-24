- I tried to figure out our pipelines after scraping and formatting to jsonlines.
    ie. storage and processing
    - in live production env there would be a lot of data, from fundamentas but more from  technical
    - we choose hadoop because we learned from our 230P class that is is suitable for such tasks
    - for that i've choosen pydoop as a client and setup G-score from  last week as the Proof of Concept.

    - understanding hadoop and hdfs local setup was difficult so i've done that
    - pydoop setup
    - G score illustration

    - many hurdles one hurdle is to sort based on score and i've figured this took like a lot of time.
        - only sort on keys, which are symbol, so have to use secondary sort.

    - im working on figuring the muliple mappers and reducers for better inferences of other G values.
    - and i need to figure how to log effectively for pydoop, it's difficut
    - below can be skipped directly by better usage of pydoop
        - hadoop fs -copyFromLocal /mnt/c/ms@uci/295P/keystone/tmp/results.jsonlines /keystone/input_2/results_2