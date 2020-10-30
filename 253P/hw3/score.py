class Solution:
    def scoreOfParentheses(self, S: str) -> int:
        def score(start, end):
            if start >= len(S) or end >= len(S):
                return 0
            elif start + 1 == end:
                return 1
            else:
                return 2*score(start+1, end-1) + (0 if end+1 not in match else score(end+1, match[end+1]))
        stack = []
        match = {}
        for i in range(len(S)):
            if S[i] == '(':
                match[i] = None
                stack.append((i, ')'))
            else:
                match[stack.pop()[0]] = i
        return score(0, len(S)-1)

if __name__ == "__main__":
    s = Solution()
    print(s.scoreOfParentheses("(()(()))"))