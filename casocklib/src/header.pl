#!/usr/bin/perl -w

use strict;

my $file;

foreach $file (`find casock/ -name '*.cc'`)
{
  chomp $file;
  print "file: $file\n";

  my $header = `grep Copyright $file`;

  if (not $header)
  {
    my $filename = $file;
    $filename =~ s/\//\\\//g;
    $filename =~ s/\./\\\./g;

    print "cat HEADER $file | sed -e 's/\\\[file name\\\]/$filename/g' >$file.new\n";
    system "cat HEADER $file | sed -e 's/\\\[file name\\\]/$filename/g' >$file.new";
    system "mv $file.new $file";
#    system "svn propset svn:keywords \"LastChangedBy LastChangedDate Revision\" $file";
  }

=comment
  my $guard = `grep '#ifndef' $file | grep -v __CGTL__`;

  if ($guard)
  {
    chomp $guard;
    $guard = substr $guard, 8;

    my $newguard = $file;
    $newguard =~ s/\//_/g;
    $newguard =~ s/\./_/g;
    $newguard = uc $newguard;
    $newguard = '__CGTL__'.$newguard.'_';

#    system "sed -e 's/$guard/$newguard/g' $file >$file.new";
#    system "sed -e 's/#endif/#endif \\\/\\\/ $newguard/g' $file.new >$file";
  }
=cut
}
