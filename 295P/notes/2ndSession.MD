- scrapy item pipelinens and framework: https://towardsdatascience.com/a-minimalist-end-to-end-scrapy-tutorial-part-ii-b917509b73f7
    - **Configured whole scraping pipeline so that next week teammates can easily jump into scraping after a quick walkthrough.**
        - **uniform statergy to scrap from all different layouts of .html**
            - search via xml path for text contains of "required", traverse sibling to get value.
        - **single point for value parser for prefix + - and suffix K(thousand) M(million) B(billion) T(trillion).**
    - **create Item and Item pipelines, as it seperates from extraction from processing, which provides**.
        - **faster modifiability.**
        - **add pre post processing.**
        - **defines prefereed structure and endpoint for db operations.**
    
    - tested with scraping book value, earning, daily volume, shares outstanding resutls.jsonlines
    - processing normalized prices.

- **dealing with missing data during processing.**
    - MCAR, MAR, MNAR?
    - https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3668100/
        - **Regression imputation:** replacing missing data with a probable value estimated by other available information.
        - **Pairwise deletion:** eliminates information only when the particular data-point needed to test a particular assumption is missing.
    - file:///C:/Users/asus/Downloads/DealingwiththeProblemofMissingData-AshortNote.pdf Geometric mean.

**AFTER finalizing how to scrap effeciently we needed to figure WHAT to scrape**
- how to use the fundamentals and technical data
    - fundamental:
        - one paper outstood: Machine Learning for Stock Prediction Based on Fundamental Analysis Yuxuan Huang.
            - examings Adaptive Neural Fuzzy Inference System (ANFIS), FeedForward Neural Network (FNN) and Random Forest (RF).
            - measured relative return wrt benchmakr index. 
            - RF model achieves the best prediction results.
            - top 6 features
                - ∆𝑃𝐵: % change of price per book
                - 𝑅𝑒𝑙𝑎𝑡𝑖𝑣𝑒_𝑟𝑒𝑡𝑢𝑟𝑛: Past quarter relative return on price
                - ∆𝐵𝑜𝑜𝑘_𝑣𝑎𝑙𝑢𝑒: % change of book value
                - ∆𝑃𝐸: % change of price per earning
                - ∆𝐶𝑎𝑝𝑖𝑡𝑎𝑙_𝐸𝑥𝑝: % change of capital expenditure
                - ∆𝐿𝑖𝑎𝑏𝑖𝑙𝑖𝑡𝑖𝑒𝑠: % change of total liabilities
            - pointed to F-score and G-score
        - **i focused on fundamental analysis strategy of G-score**: Partha S. Mohanram paper Separating Winners from Losers among Low Book-to-Market Stocks using Financial Statement Analysis.
            - **which calculates 8 Growth(G) signals.**
            - **assumptions that BM effect for low BM firms is a mispricing effect and not a risk effect.**
                - firms with low BM(book-to-market ratio) earn significant negative excess returns, while firms with high BM earn significant positive excess returns
            **is calculated using**
            - **Category 1: *earnings and cash flow* based fundamentals. ROA = net income / total assets.**
                - G1: **ROA** is greater than the contemporaneous industry median and 0 otherwise.
                - G2: **cash flow ROA** exceeds the contemporaneous industry median and 0 otherwise.
                - G3: **cash flow from operations exceeds net income** and 0 otherwise.
            - **Category 2: stock market’s *naïve extrapolation of current fundamentals*.**
                - G4: **earnings variability** is less than the contemporaneous industry median and 0 otherwise.
                - G5: firm’s **sale growth variability** is less than the contemporaneous industry median and 0 otherwise.
            - **Category 3: *impact of conservatism* on the book-to-market ratio.**
                - G6, G7 and G8: to equal 1 if a firm’s **R&D, capital expenditure and advertising intensity** are greater than the contemporaneous industry medians of the corresponding variables and 0 otherwise.

