import math

off_0 = 11.88
off_1 = 26.82

x = 0
y = 25
z = 150

s = 107
w = 105
ds = 35
dx = 25
r = 18

print("dx_test")
print(math.sqrt(2 * dx**2 ))

lSteuerArm = 117
l2 = 35
l4 = s

h1 = math.sqrt(off_0**2 + off_1**2)
h2 = math.sqrt(z**2 + y**2)

a0 = math.atan(y/z)
a1 = math.atan(off_1/off_0)
a2 = math.atan(off_0/off_1)
a3 = math.asin(h1 * math.sin(a2 + math.radians(90))/h2)
a4 = math.radians(90) - (a3 + a2)
a5 = a1 - a4

theta_h = a0 - a5
r_0 = (h1 * math.sin(a4))/math.sin(a3)

print("Wert r_0")
print(r_0)

h = math.sqrt(r_0**2 + x**2)

print("Wert h")
print(h)

phi = math.asin(x/h)

print("phi:")
print(math.degrees(phi))

print("ACOS Wert theta_s:")
print((h**2+s**2-w**2)/(2*h*s))

theta_s = math.acos((h**2 + s**2 - w**2)/(2 * h * s)) - phi

print("Theta_s")
print(math.degrees(theta_s))

a6 = math.asin(dx/ds)

print("a6 in grd:")
print(math.degrees(a6))

a7 = math.radians(180) - (theta_s + a6)

print("a7 in grd:")
print(math.degrees(a7))

a8 = theta_s + a6

print("a8 in grd:")
print(math.degrees(a8))

a9 = math.acos(dx/ds)

#theta_w1 = (a8 + a7)/2 - math.radians(90)
theta_w1 = (a8 + a7 - math.radians(180))/2

theta_w = math.acos((w**2 + s**2 - h**2)/(2 * w * s))

print("Theta_w:")
print(math.degrees(theta_w))
print(theta_w)

"""
print("Theta_w1")
print(math.degrees(theta_w1))

print("ACOS Wert theta_w:\t")
print((w**2 + s**2 - h**2)/(2 * w * s))

theta_w = math.acos((w**2 + s**2 - h**2)/(2 * w * s))


print("ACOS Wert theta_sa:\t")
print((math.sin(theta_w1-theta_w) * lSteuerArm)/r)

theta_sa = math.asin((math.sin(theta_w1-theta_w) * lSteuerArm)/r)
"""

e = math.sqrt(l2**2 + l4**2 - (2 * l2 * l4 * math.cos(math.radians(180) - theta_w)))

print("cos-test")
print(math.radians(120))
print(math.cos(math.radians(45)))

print("e")
print(e)
gamma1 = math.acos((l4**2 + e**2 - l2**2)/(2 * l4 * e))

print("gamma 1")
print(math.degrees(gamma1))

gamma2 = a7 - gamma1

print("gamma 2")
print(math.degrees(gamma2))

print("cos gamma2")
print(math.cos(gamma2))

d = math.sqrt(ds**2 + e**2 - 2 * ds * e * math.cos(gamma2))

print("d")
print(d)

print("Problem:")
print(d/lSteuerArm)

#theta_sa = math.asin(math.sin(math.acos(d/lSteuerArm)) * (lSteuerArm/r))
#theta_sa = math.asin(math.sin(math.acos(0.2)) * (lSteuerArm/r))

thetaStandardAngle = math.radians(60)

theta_sa = math.radians(180) - (a8 + a9)
theta_sa_corr = thetaStandardAngle - theta_sa

print("Hüftwinkel:\t")
print(math.degrees(theta_h))
print("Schulterwinkel:\t")
print(math.degrees(theta_s))
print("Steuerwinkel:\t")
print(math.degrees(theta_sa))
print("Steuerwinkel korrigiert:")
print(math.degrees(theta_sa_corr))
