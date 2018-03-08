fib(X, Y):-
  fib1(0, 0, 1, X, Y).
fib1(N, F, _, N, F).
fib1(N1, A, B, N, F):-
  N1<N,
  N2 is N1 + 1,
  C is A + B,
  fib1(N2, B, C, N, F).
