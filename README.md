# CGH
What this program aims to do is to generate a hologram based on a binary 64x64 object, saved in a text file.
The program consists of a basic graphical UI, in which user can select options he wants and set the properties of generated images, like color and whether or not to generate a chart.
The names of variables are written mostly in Polish, which is a subject to change in the future.

I utilized SFML libraries by SFML-Team (GitHub link - https://github.com/SFML/SFML) and some ugly textures I made myself, but plan to change them once I find some time. They are sort of placeholders as of now.

The output of the program are some .txt files, which contain data processed by the program. They are not really useful, but can prove so if you want to analyze the images generated by the program.
Staying on the topic of images - the program generates 4 images:
1. the data on the input as a .png file. To be quick - the program reads data, translates to image and outputs it here. The name is 'obiekt.png'.
2. data processed as a spectrum of an image. It is made by using a Fast Fourier Transformation on the object. The name of the file is 'widmo.png'.
3. the hologram - a spectrum but considering phase and amplitude. This is in fact the most important image, that can be projected. Plus it looks quite nice :) The name of the image is 'widmo_hologram.png'
4. hologram that was processed once more, but the other way around, with the Fourier transformation - to put it simply. It shows how quantization impacts the result. The name of the file is 'obraz.png'.


This was my school project for a contest, called "Olympics of Technical Innovation 2019". Of course the title is translated from Polish. I took the 2nd place in my region and didn't make it to the next stage, sadly. But for a beginner programmer it's a huge success that someone appreciated my efforts and wanted to work with me.

The Fast Fourier Transformation (FFT) was prepared by my project coordinator - Krzysztof Łyszczek, who gave the idea and was the inspiration for all this mess. I have his permission to upload it here and I am really grateful for all the hard work he did to teach me some stuff about physics and how optics work.
