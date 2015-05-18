def reverse(iter):
	head = next(iter)
	if head == 'x':
		ul, ur, dl, dr = [ reverse(iter) for _ in range(4) ]
		head = "".join( [head, dl, dr, ul, ur] )
	return head

for _ in range( input() ):
	print reverse( iter(raw_input()) )