# Lion

This is an evasive payload for EDRs that I developed some time ago to learn malware development.

The payload uses Fibers to execute shellcode in-memory and fibers won't create kernel callbacks so that would prevent hits to an EDR if they monitor callbacks.
Nothing particularly serious in terms of encryption and string hashing, it uses RC4 to decrypt the shellcode located in  `.RSRC` section of the PE. 

Byte patch of ETW is included however not a good idea as its well known by vendors and will be detected so something like HWBP and VEH to patch ETW is better.

I've had good success with this against Defender ATP.

# Disclaimer
The creator of this program does not hold liability of how this code is used. This is was created purely for educational purposes only and should only be used in a safe and secure environment where permissions have been granted by the owner.
