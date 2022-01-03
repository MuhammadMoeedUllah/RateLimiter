# RateLimiter
![CircleCI](https://circleci.com/gh/MuhammadMoeedUllah/RateLimiter.svg?style=shield)
![Coverage Badge](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/MuhammadMoeedUllah/52019294b0eaaae8927f305e7c1b7052/raw/test.json)


<br />
<br />


In web based applications we face restrictions on number of API calls made for example in aws services. To control those calls on a time scale we can use a rate limiter. 

To run the project use following steps
```
mkdir build
cd build
cmake ..
```

This will setup the project. Now let's build the executable as following

```
make 
```

Now run the executable. 
```
./RateLimiter
```

That's it. In future changes I will be adding testing and logging using some public libraries
for exmple spdlog and Catch2 for unit testing.



