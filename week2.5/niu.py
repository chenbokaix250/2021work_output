import itertools,sys

def cards():
	cards = {'黑桃A':1,'红桃A':1,'方片A':1,'梅花A':1}
	card_type = ['黑桃','红桃','方片','梅花']

	for c_type in card_type:
		for no in range(2,11):
			cards[c_type + str(no)] = no

		for name in ['J','Q','K']:
			cards[c_type + name] = 10

	return cards


def all_cases(cards):
	return list(itertools.combinations(cards,5))

if __name__ == '__main__':
	cards = cards()
	all_cases = all_cases(cards)

	print(len(all_cases))

	for case in all_cases:
		temp_name = list(case)
		temp_value = []
		for ca in case:
			temp_value.append(cards[ca])

		sums = sum(temp_value)
		if sums % 10 == 0:
			s_cases = list(itertools.combinations(temp_name,3))
			for s_case in s_cases:
				temp_name2 = list(s_case)
				temp_value2 = []
				for s_ca in s_case:
					temp_value2.append(cards[s_ca])

				sumc = sum(temp_value2)
				if sumc % 10 == 0:
					print(temp_name)
					break