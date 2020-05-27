modelname = "sortieR.data"
data = read.table(modelname)
attach(data)

iteration = V1
resultatTSP = V2

plot(iteration,resultatTSP,type="l",xlab="iteration",ylab="resultatTSP en m",col="red")
