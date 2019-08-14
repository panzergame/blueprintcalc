ai = [1, 2, 3]
bi = [11.5, 14, 15.5]

n = len(ai)

c1 = n
c2 = 0
c3 = 0
c4 = 0
c5 = 0

# Calcul des constantes
for a, b in zip(ai, bi):
	c2 += b ** 2
	c3 += 2 * a * b
	c4 += 2 * b
	c5 += 2 * a

# Recherche du minimum (le seul point critique)
d = 4 * c1 * c2 - c4 ** 2
s = (2 * c1 * c3 - c4 * c5) / d
t = -(c3 * c4 - 2 * c2 * c5) / d

print(s, t)

for a, b in zip(ai, bi):
	nb = b * s + t
	print(a, nb, abs(a - nb))
