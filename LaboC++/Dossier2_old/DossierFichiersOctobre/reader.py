#!/usr/bin/python2
# -*- coding: Utf-8 -*-
# Raphael Javaux - 2 nov. 2010

import struct # C's structs reader

import pygtk, gtk
pygtk.require('2.0')

KEY_SEPARATOR = '\0'
FREESPACE_COLOR = gtk.gdk.color_parse('#A4E386')
PADDING_COLOR = gtk.gdk.color_parse('#E3A67B')

def info_dialog(title, dic = {}):
	def key_value_box(key, value):
		box = gtk.HBox(True)
		
		key_label = gtk.Label()
		key_label.set_markup('<b>{0}</b>'.format(key))
		box.pack_start(key_label)
		box.pack_start(gtk.Label(value))
		return box
	
	dialog = gtk.Dialog('Details {0}'.format(title))
	dialog.set_size_request(200, 100)
		
	for key, value in dic.iteritems():
		dialog.vbox.pack_start(key_value_box(key, value))
	
	dialog.show_all()

class Element():
	def __init__(self, in_file_offset, offset, size, key, value):
		self.in_file_offset = in_file_offset
		self.offset = offset
		self.size = size
		self.key = key
		self.value = value
		
	@property
	def total_size(self):
		return self.size + 6
		
	@property
	def padding(self):
		return (4 - (self.total_size % 4)) % 4;
	
	@property
	def freespace(self):
		return self.offset - (self.total_size + self.padding)
		
	@property
	def widgets(self):
		def space_button(callback, title=None, color=None, width=-1):
			but = gtk.Button(title)
			if color != None:
				but.modify_bg(gtk.STATE_NORMAL, color)
				but.modify_bg(gtk.STATE_PRELIGHT, color)
			
			but.set_size_request(width, -1)
				
			but.connect('clicked', callback)
			
			return but
			
		yield space_button(self.details, title=self.key, width=max(25, self.total_size * 4))
		
		if self.padding > 0:
			yield space_button(self.details_padding, color=PADDING_COLOR, width=self.padding * 4)
		
		if self.freespace > 0:
			yield space_button(self.details_libre, color=FREESPACE_COLOR, width=max(25, self.freespace * 4))

	def details(self, event):
		info_dialog(self.key, { 'In file offset' : self.in_file_offset,
			'Offset' : self.offset,
			'Size' : self.size,
			'Total size' : self.total_size,
			'Key' : self.key,
			'Value': self.value
		})
		
	def details_padding(self, event):
		info_dialog('padding ({0})'.format(self.key),
			{ 'In file offset' : self.in_file_offset + self.total_size,
			'Padding' : self.padding
		})
	
	def details_libre(self, event):
		info_dialog('freespace ({0})'.format(self.key),
			{ 'In file offset' : self.in_file_offset + self.total_size + self.padding,
			'Free space' : self.freespace
		})

class Toolbar(gtk.Toolbar):
	def __init__(self, win):
		super(Toolbar, self).__init__()
		
		self.win = win
		
		self.open_but = gtk.ToolButton(gtk.STOCK_OPEN)
		self.open_but.connect('clicked', self.open)
		self.refresh_but = gtk.ToolButton(gtk.STOCK_REFRESH)
		self.refresh_but.connect('clicked', self.refresh)
		
		self.insert(self.open_but, -1)
		self.insert(self.refresh_but, -1)
	
	def open(self, event):
		dialog = gtk.FileChooserDialog(title='Choisissez un fichier',
			action=gtk.FILE_CHOOSER_ACTION_OPEN,
			buttons=(gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL, gtk.STOCK_OPEN, gtk.RESPONSE_OK)
		)
			
		response = dialog.run()
		if response == gtk.RESPONSE_OK:
			self.win.file.file = dialog.get_filename()
		
		dialog.destroy()
	
	def refresh(self, event):
		self.win.file.refresh()
	
class File(gtk.ScrolledWindow):
	def __init__(self, win):
		super(File, self).__init__(hadjustment=None, vadjustment=None)
		
		self.hbox = gtk.HBox()
		
		self.add_with_viewport(self.hbox)
		self.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_NEVER)
		
		self.file = None
	
	@property
	def file(self):
		return self._file
	
	@file.setter
	def file(self, value):
		self._file = value
		self.refresh()
	
	def refresh(self):
		if self.file != None:
			try:
				self.clear()
				for elem in self.gen_elements():
					for widget in elem.widgets:
						self.hbox.pack_start(widget, False, False)
			except Exception as e:
				self.clear()
				self.hbox.pack_start(gtk.Label("Erreur"))
				print (e)
			
			self.hbox.show_all()
	
	def gen_elements(self):
		def read_headers(f):
			data = f.read(6)
			
			if data:
				return struct.unpack('ih', data) # (int offset, short size)
			else:
				return None
		
		def read_data(f, length):
			def list_to_str(l):
				return reduce(lambda acc, val: acc + str(val), l, "")
			
			key = []
			value = []
			curr = key
			for byte in f.read(length):
				if byte == KEY_SEPARATOR:
					curr = value
				else:
					curr.append(struct.unpack('c', byte)[0])
			
			return list_to_str(key), list_to_str(value)
		
		with open(self.file) as f:
			in_file_offset = 0
			headers = read_headers(f)
			while headers != None:
				data = read_data(f, headers[1])
				
				yield Element(in_file_offset, headers[0], headers[1], data[0], data[1])
				
				f.seek(headers[0] - (headers[1] + 6), 1)
				in_file_offset += headers[0]
				
				headers = read_headers(f)
	
	def clear(self):
		self.hbox.foreach(lambda widget: self.hbox.remove(widget))

class Window(gtk.Window):
	def __init__(self):
		super(Window, self).__init__()
		
		self.set_title('Lecteur de fichier')
		self.set_size_request(700, 100)
		
		self.vbox = gtk.VBox()
		
		self.toolbar = Toolbar(self)
		self.file = File(self)
		
		self.vbox.pack_start(self.toolbar, False, False)
		self.vbox.pack_end(self.file)
		self.add(self.vbox)
		
if __name__ == '__main__':
	win = Window()
	win.show_all()
	
	#win.file.file = 'test.txt'
	
	gtk.main()
