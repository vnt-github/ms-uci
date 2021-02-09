- TODO:
    - [ ] lectures
    - [ ] email
    - [ ] piazza

- presenters revolve between weeks, though anyone can answer.
- twice per quarter we perform project and code review, no group evaluate same group twice. professor/TA decides which group to review.

- professor have not expectations
    - have you been spending time wisely.
    - first two week planning architecture how you want.
    - what have you done?
    - has it been useful?
    - do you have any question?
    - should be getting results by week 2 or 3.

- public competetion aspect
    - groups working on same project will compete with each other post anonymolously.
    - agreed upon method of evaluation.
        - ?
    - where you rank by far is not gonna be the solve factor determining the grade.

- are we are gonna be evaluated every single week?

- is the risk analysis part of stock picking applied here?

- grades are based on the updates each week.

- measure by which the output is choosen is fixed.

- what is the measure of output quality?

- lecture2 47 min: machine learning stock price predictor model
    - presenter:
        - gathering the data: yahoo finance, professor data.
        - stock market anaylysisk, stock market prediction.
        - goal comparison to random stock predictor(S&P500 index) trader for diff stocks and time, our should be better.
        - some certain stocks are better or predictable than others?
        - are some relationship between stocks and some financial indicators?
    - professor:
        - algo developed performed no better than stock pickers, chat rooms(zacks.com).
        - if millions of people are constantly monitoring then eventually all the secrets or indicators are out.
        - so moslty big hedge funds, who gets sse -> ml -> buy, sell, hold etc
        - pretend it's 2007 how will it perform.
        - what kinds of profits you could have made using historical data?
        - risk analysic is quite different from stocks picker.
        - suggest easiest data is professors data.

- shitty data handling?
    - how do you extrace right data from html.
    - scraping and cleaning data and making sure it's reliable.
    - numbers are junk itself.

- presenter: risk is preety much unavoidable.

- news: News (social media & financial news),

---
lecture 3:
- IPO: initial  public offering is best but rare.

- market sell: sell for the best bid available, then buyers are sorted by descending bid and sell the volume of stocks max(available, asked).
- companies are bound by law to list RISKS.
- learn as much about the company to make decision.
    - like risks, sentiment etc.
    - earnings per dollar
    - insaurance premium per dollar.
    - cost per dollar.
    - projected growth for next 10 years per dollar.
    - book value per dollar.

- buyer and seller how to determine the price?
    - current worth value?
        - current worth actual value is useless.
        - it is how much it's worth to you.
            - long term prospects.
                - stable
                - good management team
                - what kinds of deals
                - what is the future cash flow. 
                - where is the manifcaturing facility.
                - READ ABOUT THE COMPANIES OPINION online.
        - ANS: it's the future potential
            - it should be less that what you'll get than tmmrw.
            - 

- fundamental information of companies:
    - report: quarter, yearly
        - actual earning: total money made
        - actual cost: expension for product
        - profit = actual earning - actual cost.
        - stocks outstanding: total number of stocks of a company
        - earning per share = profit / stocks outstanding.
        - book value: the current value of everything owned by company.
        - apr(Annual percentage rate), projects gains per year/annum.
            - value is gonna be 20 times in next 10 years so it's APR = 20^(⅒)
            - also compare with inflation as inflation is also 2% pa in guestimate, so it must be greater that inflation.
        - what is debt of the company?
        - how much customer they have.
        - how much cash they have.
        - how much real estate they have.
        - how many employees they have.
        - how is the employee payroll they have. expensive or cheap.
        - earning per share normalize by share price = earnings per dollar.

- PER SHARE STUFF DOESN"T MAKE SENSE TO PROFESSOR.
    - because each share prices can be different for diffent companies
    - so we need to get per dollar. by dividing stocks price of a company.

- measures of success:
    - raw profit with 20% increase in 2 years.
    - risk: amount of fluctuation.
        - sharp ratio: gain/sqrt(variance of gain)
            - value of 1.7 is considered preety good.
            - value below 1 is preety risky, as fluction is same size as gain.

- look at fundamentals and historical data.
- heard mentality is exploted by hater index.
    - if people watch stocks too carefully and they see it going down then people are gonna sell frantically of good stocks.
    - scouring social media.
    - hater index would exploit the fluctuaction and heard mentality to predict actions of BUY, SELL, HOLD etc.

- June 12 lecture 1:14: HATER INDEX TO BE MILLED TOGETHER WITH TACTICAL DATA, no social media on old data but will have REUTERS news articles.
- will keep some data behind to evaluate the predictions.

- high volume: low bid-ask spread typically 0.01 $
- low volume: high bid-ask spread. 0.45 $ is big.
- instantaneous buy and sell are always a loss.

- jan 19 51: what is exctly we are going to predict.
    - trying to make a profit.
    - if buy a share today and sell in future(day, monts, year), only allowed to use information available today
    - make a portfolio: pick 10 stocks wait a month and sell on profit.
    - on tactical trading of daily buy/sell of [may be thinly traded] like in hater index the 0.01 profit matters.

- stocks volume: no of shared traded,
- cash volume of a stock: no share traded * AVG PRICE OF THE DAY.
    - allows companies independent of stocks price.

- because 1 share of Berkshire Hathaway BRKA: is 200k$, BRKB: 2k-4k$.

- thinly traded has the problem of high bid-ask rate.
- thinly traded has another problem is then stock available to buy is no much.

- gotachas for real trading
    - "large trade affects the market"
        - if i buy a lot of stocks of a company than that trade will change stock price of company.
        - then people are gonna notice and gonna start competing with you.
        
        - how to counter this?
            - plot cash volume vs bid ask on log scale, it is inversely linear on log scale.
            - pick the range of cash volume and buy at top and sell at bottom.
        
        - commission: there is also a trade cost associated with exchanges. which is for ex 0.001/share.
            - so buying and selling at same still has loss due to trade cost.

- pair companies:
    - use two different companies for getting better results.
    - extrapolations: compare similar companies on different parts of world. like japanses vs US.

- open high low close volume
    - don't know the times associated with high and low.
    - pick value between hight and low.
        - gaussian/random number generator focused around the centre.
        - uniform: in between.
        - pessmistic: buy at daily hight and sell ant daily low.
        - never use hight and low or open and close.
- jan 19 1: 24
    - buy a portfolio of 100 stocks(equal amount of dollar price for each) and sell ofter 1 month (use historical prices on march 1).
    - run a simulations of portfolio 1000 times.
    - use friction for trading.
    - make more realisting more impressed.
    - period acc. to professor data is 5 years from now, or monthly.
    - benchmakr is the s&p 500 to be compared with.

- jan 21:
    - cash per dollar - debt per dollar = bank
    - negative bank value is red flag is red flag.
    - not unless if they have large cash flow.
    - value of company = bank + epd + ...
    - value > 1 is each dollar spend we'll get 1 dollar worth of value. very good buy.
    - -1 or worse not good idea.
    - understand the system and simplify it, then making predictable is easy.
    - hard part HTML SCRAPPING OF PROFESSOR DATA is non trivial.
    - 1:26 : No, don't scrape other source
        - you'll not be able to get the professors data.
        - maybe try and see what you can find for october altera ALTR. of the fundamentals.
        - insider informations is also available which professors thinks we can't find anywhere else.