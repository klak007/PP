#1
alias lt='ls --human-readable --size -1 -S --classify'
#2
del_arg="5"
rm *$del_arg*
#3
d=10 #days since last modification
find -ctime -$d | grep -r "polska" 

#4

for file in *.JPEG; do
    mv "$file" "${file%.JPEG}.jpeg"
done

for file in *.JPG; do
    mv "$file" "${file%.JPG}.jpg"
done

for file in *.PNG; do
    mv "$file" "${file%.PNG}.png"
done
#5
dir_copy=Documents/kwadraty/książki
dir_paste=Documents/kwadraty/książki2
find $dir_copy  -name '*.JPG' | 
cpio -pmdv  $dir_paste |
cd $dir_paste/$dir_copy
for file in *.JPG; do 
    mv "$file" "${file%.JPG}.jpg" 
done 
rename "s/ /_/g" *
#7
sendmail aleks.klak@gmail.com < email.txt

