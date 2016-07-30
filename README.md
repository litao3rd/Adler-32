# Adler-32 checksum

This is a simple implementation for adler32 checksum algorithm.

All the details for this algorithm please visit [wikipedia](https://en.wikipedia.org/wiki/Adler-32)

In this repo, I left two test cases.

One from wikipedia webpage. That the Adler-32 sum of the ASCII string "Wikipedia" is 0x11E60398.

The other test case is a classes.dex file that used in Android APK file. 

In android apk file, adler-32 is used in dex file for a simple check. It remove the magic and checksum fields(first 12 bytes of the classes.dex file), then calc its adler-32 checksum for fill the checksum field.

The classes.dex in this repo I have already remove the magic and checksum fields from the original file,
so you can just use it for test. Its adler-32 checksum is `0x4A3BFC25`
