library("lattice")
x <- seq(1,10, length.out=20)
y <- seq(1,10, length.out=20)
data <- expand.grid(X=x, Y=y)
data$Z <- runif(400, 0, 5)
levelplot(Z ~ X*Y, data=data  ,xlab="X",
          main="")

data <- matrix(runif(100, 0, 5) , 10 , 10)
colnames(data) <- letters[c(1:10)]
rownames(data) <- paste( rep("row",10) , c(1:10) , sep=" ")

# plot it flipping the axis
levelplot(data)

data <- matrix(runif(100, 0, 5) , 10 , 10)
colnames(data) <- letters[c(1:10)]
rownames(data) <- paste( rep("row",10) , c(1:10) , sep=" ")

# plot it flipping the axis
levelplot( t(data[c(nrow(data):1) , ]),
           col.regions=heat.colors(100))
data[1,3]
