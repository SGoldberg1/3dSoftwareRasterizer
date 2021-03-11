
local_persist s8 CHAR_NUMBERS[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

//RETURNS A LOWER CASE LETTER(ASCII)
inline s8
ToLowerChar(s8 character)//HACK(stephen):ONLY WORKS FOR ALPHA
{
    s8 result = character;
    if(IsClampedInclusive_S8(result, 'A', 'Z'))
        result = (result + 32);
    return(result);
}

inline s8
ToUpperChar(s8 character)//HACK(stephen):ONLY WORKS FOR ALPHA
{
    s8 result = character;
    if(IsClampedInclusive_S8(result, 'a', 'z'))
        result = (result - 32);
    return(result);
}

inline void
ReverseString(char* buffer,
              s32 length)
{
    char tempChar = 0;
    
    for(s32 i = 1; i < length; i++)
    {
        tempChar = buffer[i - 1];
        buffer[i - 1] = buffer[length - i];
        buffer[length - i] = tempChar;
    }
}

// TODO(Stephen): IMPLEMENT PROPER FLOAT CONVERSION
//THIS IS A HACK!!!
r32
ConvertString_R32(s8* string)
{
    r32 result = 0;
    s8* character = string;
    s32 currentValue = 0;
    s32 division = 1;
    b32 hasDecimal = FALSE;
    b32 isNegative = FALSE;
    
    while(*character)
    {
        if(*character == '.')
        {
            hasDecimal = TRUE;
        }
        else if(*character == '-')
        {
            isNegative = TRUE;
        }
        else
        {
            if(hasDecimal)
                division *= 10;
            
            currentValue *= 10;
            currentValue += (*character - '0');
        }
        
        ++character;
    }
    
    result = currentValue / (r32)division;
    
    if(isNegative)
        result *= -1.0f;
    
    return(result);
}

s32
ConvertString_S32(s8* string)
{
    s32 result = 0;
    s8* character = string;
    s32 currentValue = 0;
    b32 isNegative = FALSE;
    
    while(*character)
    {
        if(*character == '-')
        {
            isNegative = TRUE;
        }
        else
        {
            currentValue *= 10;
            currentValue += (*character - '0');
        }
        
        ++character;
    }
    
    result = currentValue;
    
    if(isNegative)
        result *= -1;
    
    return(result);
}

inline s32
ConvertS32_String(char* buffer,
                  s32 value)
{
    b32 isNegative = (value < 0);
    value = Abs_R32(value);
    s32 index = 0;
    buffer[index] = '0';
    s32 currentDigit = 0;
    
    if(value)
    {
        while(value != 0)
        {
            currentDigit = (value % 10);
            value = (value / 10);
            buffer[index++] = CHAR_NUMBERS[currentDigit];
        }
        
        if(isNegative)
        {
            buffer[index++] = '-';
        }
        
        ReverseString(buffer, index);
    }
    else
        ++index;
    
    return(index);
}

// TODO(Stephen): IMPLEMENT PROPER FLOAT CONVERSION
//THIS IS A HACK!!!
inline void
ConvertR32_String(char* buffer,
                  r32 value,
                  s32 percision = 2)
{
    b32 isNegative = (value < 0);
    s32 index = 0;
    buffer[index] = '0';
    s32 wholeNumber = (s32)value;
    r32 decmialNumber = (Abs_R32(value) - (r32)Abs_R32(wholeNumber));
    char* lastLetter = &buffer[ConvertS32_String(buffer, wholeNumber)];
    
    if(percision)
    {
        *lastLetter++ = '.';
        
        while(percision > 0)
        {
            decmialNumber *= 10.0f;
            wholeNumber = (s32)(decmialNumber);
            ConvertS32_String(lastLetter++, wholeNumber);
            decmialNumber = (decmialNumber - (r32)wholeNumber);
            --percision;
        }
    }
}

//GENERATES A RANDOM NUMBER FROM GIVEN PATTERN
//NOTE(stephen): PATTERNS i.e. "cvvc"
//               C = CONSONANT
//               V = VOWEL
//               INDEX 0 OF "cvvc" -> CONSONANT
//               INDEX 1 OF "cvvc" -> VOWEL
//ETC..
void
GetRandomName(s8* buffer, //BUFFER TO STORE GENERATED NAME
              s8* pattern, //PATTERN OF THE GENERATED WORD
              s32 patternLength)//LENGTH OF THE PATTERN/NAME
{
    local_persist s8 consonants[20] =
    {
        'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
        'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z'
    };
    local_persist s8 vowels[6] = { 'a', 'e', 'i', 'o', 'u', 'y' };
    
    s8 character = 0;
    s8 patternChoice = 0;
    
    for(s32 i = 0; i < patternLength; ++i)
    {
        patternChoice = pattern[i];
        
        if(patternChoice == 'c')
        {
            character = consonants[Random_S32(0, 20)];
        }
        else
        {
            character = vowels[Random_S32(0, 6)];
        }
        
        if(i == 0)
            character = ToUpperChar(character);
        
        buffer[i] = character;
    }
}
