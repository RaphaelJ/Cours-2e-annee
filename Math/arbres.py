class Arbre:
	def __init__(val, gch, dte):
		self.val = val
		self.gch = gch
		self.dte = dte

	def max():
		if self.dte == None:
			return self.val
		else:
			return self.dte.max()

	def ajouter(val):
		if val < self.val:
			if self.gch == None:
				self.gch = Arbre(val, None, None)
			else:
				self.gch.ajouter(val)
		else:
			if self.dte == None:
				self.dte = Arbre(val, None, None)
			else:
				self.dte.ajouter(val)

	def supprimer():
		""" Supprime le noeud courrant """
		if self.gch == None:
			self.val = self.dte
		elif self.dte == None:
			self.val = self.gch
		else:
			self.val = self.gch.max()
