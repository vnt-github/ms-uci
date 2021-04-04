- project idea: make blockchain or p2p and use in 295P.
- read about block chain.


# these each quaterly value need to be sum verify the Revenue (ttm) and sum of Total Revenue
values = map(self.convert_str_to_number, total_assets_selectors.xpath("../td/b/text()").getall()[1:])
return sum(each*1000 for each in values if each is not None)
