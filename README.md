# Computer Operating system: ProcessResourceManage
 
💡Test example
Enter the test command or place the test command in the test file input.txt with the following content

cr x 1  
cr p 1  
cr q 1  
cr r 1  
to  
req R2 1  
to  
req R3 3  
to  
req R4 3 to  
to  
to  
req R3 1  
req R4 2  
req R2 2  
to  
de q  
to  
to  

The output should read: init x x x x x p p q q r r x p q r x x x p x
