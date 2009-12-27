#!/fs/sz-user-supported/Linux-i686/bin/python2.5
from optparse import OptionParser
import os

############################################################
# correct.py
#
# Launch pipeline to correct errors in sequencing reads.
############################################################


############################################################
# main
############################################################
def main():
    parser = OptionParser()
    
    parser.add_option('-r', dest='readsf', help='Fastq file of reads')
    parser.add_option('-k', dest='k', type='int', help='Size of k-mers to correct')

    (options, args) = parser.parse_args()

    if not options.readsf:
        parser.error('Must provide fastq file of reads with -r')
    if not options.k:
        parser.error('Must provide k-mer size with -k')

    kmerf = os.path.splitext( os.path.split(options.readsf)[1] )[0]

    # pull out sequence
    os.system('formats.py --fq2fa %s > %s.fa' % (options.readsf, kmerf))
    
    # count mers
    os.system('meryl -B -C -m %d -s %s.fa -o %s' % (options.k, kmerf, kmerf))
    # print histogram of counts
    os.system('meryl -Dh -s %s > %s.hist' % (kmerf,kmerf))
    # print counts
    os.system('meryl -Dt -n 1 -s %s > %s.cts' % (kmerf,kmerf))

    # find trust/untrust boundary
    boundary = find_boundary(kmerf)

    print boundary
    

############################################################
# find_boundary
#
# Find a good boundary between trusted and untrusted kmers
# by examining the histogram for the smallest value before
# the peak at the expected coverage
############################################################
def find_boundary(kmerf):
    last_hist = 0
    increases = 0
    
    min_ct = 0
    min_hist = 0
    
    for line in open(kmerf+'.hist'):
        a = line.split()

        # init, or lesser
        if min_ct == 0 or int(a[1]) < min_hist:
            min_ct = int(a[0])
            min_hist = int(a[1])

        # assess upward trend
        if int(a[1]) > last_hist:
            increases += 1
        else:
            increases = 0
            
        if increases >= 3:
            break

        last_hist = int(a[1])

    if increases != 3:
        print 'WARNING: Error and expected coverage peaks blurred. Boundary is %d' % min_ct

    return min_ct

        

            
############################################################
# __main__
############################################################
if __name__ == '__main__':
    main()
