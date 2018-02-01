def fib(n)
  if n < 1
    return n
  else
    a = 0
    b = 1
    for i in (1...n)
      temp = a+b
      a = b
      b = temp
    end
    return b
  end
end
