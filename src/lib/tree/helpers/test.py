import TreeDefnParser as gt

det = gt.DetType()
event = gt.EventType()


## Doing stuff

det.AddMeasurement("Double_t")
event.AddDetector(det)

event.SetGroup("DCP")
event.SetPrefix("D1")
print(event.TypeDefs())
#print(tree.TypeDefs("TEST", "D"))


det.AddMeasurement("Short_t")
event.AddDetector(det)
event.AddDetector(det)

print("\nLINKDEF\n")

print(event.LinkDefs())

print("\n ROOT2GAMR \n")

event.SetDescription("DCP 2")

print(event.root2gamr()[0])
print(event.root2gamr()[1])

defns = gt.TreeDefinitions("/home/admiralakber/git/physics/gamma-root/docs/md/tree/treetypes.md")
print("Linkdef\n",defns.LinkDefs("DCP", "D1"))
print("Typedef\n", defns.TypeDefs("DCP", "D1"))
print("Root2Gamr\n",*defns.root2gamr("DCP", "D1"))
