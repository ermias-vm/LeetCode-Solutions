import java.util.*;

// Description: https://leetcode.com/problems/encode-and-decode-strings/description/


class Solution {
    
    public String encode(List<String> strs) {
        StringBuilder encodedString = new StringBuilder();
        encodedString.append(strs.size()).append("#");
        
        for (String str : strs) {
            encodedString.append(str.length()).append("#").append(str);
        }
        
        return encodedString.toString();
    }
    
    public List<String> decode(String s) {
        int currentPos = 0;
        int hashPos = s.indexOf('#', currentPos);
        int listSize = Integer.parseInt(s.substring(currentPos, hashPos));
        currentPos = hashPos + 1;
        
        List<String> decodedStrings = new ArrayList<>(listSize);
        
        for (int i = 0; i < listSize; i++) {
            hashPos = s.indexOf('#', currentPos);
            int wordSize = Integer.parseInt(s.substring(currentPos, hashPos));
            currentPos = hashPos + 1;
            decodedStrings.add(s.substring(currentPos, currentPos + wordSize));
            currentPos += wordSize;
        }
        
        return decodedStrings;
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        
        List<String> strs1 = Arrays.asList("hello", "world");
        List<String> strs2 = Arrays.asList("", "a", "abc", "defg");
        
        String encoded1 = solution.encode(strs1);
        String encoded2 = solution.encode(strs2);
        
        List<String> decoded1 = solution.decode(encoded1);
        List<String> decoded2 = solution.decode(encoded2);
        
        System.out.println("Input 1: " + strs1);
        System.out.println("Encoded 1: " + encoded1);
        System.out.println("Decoded 1: " + decoded1);
        System.out.println();
        
        System.out.println("Input 2: " + strs2);
        System.out.println("Encoded 2: " + encoded2);
        System.out.println("Decoded 2: " + decoded2);
    }
}
