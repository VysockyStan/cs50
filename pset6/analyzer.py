import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives="positive-words.txt", negatives="negative-words.txt"):
        """Initialize Analyzer."""
        
        self.posWords = set()
        self.negWords = set()
        
        file = open(positives, "r")
        for line in file:
            if line.find(';'):
                self.posWords.add(line.rstrip("\n"))
        file.close()
        
        file = open(negatives, "r")
        for line in file:
             if line.find(';'):
                self.negWords.add(line.rstrip("\n"))
        file.close()
        
        

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text.lower())
        
        count = 0
        for i in self.posWords:
            for j in tokens:
                if j == i:
                    count += 1
                    
        for i in self.negWords:
            for j in tokens:
                if j == i:
                    count -= 1            
                    
            
        return count
