include_directories(${CMAKE_CURRENT_LIST_DIR})

list(APPEND SHARED_THIRDPARTY_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/H5ACmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5ACpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5ACprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5ACpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Amodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5api_adpt.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Apkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Aprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Apublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5B2module.h
    ${CMAKE_CURRENT_LIST_DIR}/H5B2pkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5B2private.h
    ${CMAKE_CURRENT_LIST_DIR}/H5B2public.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Bmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Bpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Bprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Bpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Cmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Cpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Cprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Cpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5CSprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5CXmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5CXprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Dmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Dpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Dprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Dpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5EAmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5EApkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5EAprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Edefin.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Einit.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Emodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Epkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Eprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Epubgen.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Epublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Eterm.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FAmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FApkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FAprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDcore.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDdirect.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDdrvr_module.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDfamily.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDlog.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDmpi.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDmpio.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDmulti.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDsec2.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDstdio.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FDwindows.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FLmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FLprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Fmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FOprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Fpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Fprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Fpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FSmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FSpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FSprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5FSpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Gmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Gpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Gprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Gpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HFmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HFpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HFprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HFpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HGmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HGpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HGprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HGpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HLmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HLpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HLprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HLpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5HPprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Imodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Ipkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Iprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Ipublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Lmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Lpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Lprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Lpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5MFmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5MFpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5MFprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5MMprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5MMpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5MPmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5MPpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5MPprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Omodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Opkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Oprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Opublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Oshared.h
    ${CMAKE_CURRENT_LIST_DIR}/H5overflow.h
    ${CMAKE_CURRENT_LIST_DIR}/H5PBmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5PBpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5PBprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5PLextern.h
    ${CMAKE_CURRENT_LIST_DIR}/H5PLmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5PLpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5PLprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5PLpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Pmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Ppkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Pprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Ppublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5private.h
    ${CMAKE_CURRENT_LIST_DIR}/H5public.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Rmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Rpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Rprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Rpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5RSprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5SLmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5SLprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5SMmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Smodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5SMpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5SMprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Spkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Sprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Spublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5STprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Tmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Tpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Tprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Tpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/H5TSprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5UCprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5version.h
    ${CMAKE_CURRENT_LIST_DIR}/H5VMprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5WBprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5win32defs.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Zmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Zpkg.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Zprivate.h
    ${CMAKE_CURRENT_LIST_DIR}/H5Zpublic.h
    ${CMAKE_CURRENT_LIST_DIR}/hdf5.h
)

list(APPEND SHARED_THIRDPARTY_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/H5.c
    ${CMAKE_CURRENT_LIST_DIR}/H5A.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Abtree2.c
    ${CMAKE_CURRENT_LIST_DIR}/H5AC.c
    ${CMAKE_CURRENT_LIST_DIR}/H5ACdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5AClog.c
    ${CMAKE_CURRENT_LIST_DIR}/H5ACmpio.c
    ${CMAKE_CURRENT_LIST_DIR}/H5ACproxy_entry.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Adense.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Adeprec.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Aint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Atest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5B.c
    ${CMAKE_CURRENT_LIST_DIR}/H5B2.c
    ${CMAKE_CURRENT_LIST_DIR}/H5B2cache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5B2dbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5B2hdr.c
    ${CMAKE_CURRENT_LIST_DIR}/H5B2int.c
    ${CMAKE_CURRENT_LIST_DIR}/H5B2internal.c
    ${CMAKE_CURRENT_LIST_DIR}/H5B2leaf.c
    ${CMAKE_CURRENT_LIST_DIR}/H5B2stat.c
    ${CMAKE_CURRENT_LIST_DIR}/H5B2test.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Bcache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Bdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5C.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Cdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Cepoch.c
    ${CMAKE_CURRENT_LIST_DIR}/H5checksum.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Cimage.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Clog.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Cmpio.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Cprefetched.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Cquery.c
    ${CMAKE_CURRENT_LIST_DIR}/H5CS.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ctag.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ctest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5CX.c
    ${CMAKE_CURRENT_LIST_DIR}/H5D.c
    ${CMAKE_CURRENT_LIST_DIR}/H5dbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dbtree.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dbtree2.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dchunk.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dcompact.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dcontig.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ddbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ddeprec.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dearray.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Defl.c
    #${CMAKE_CURRENT_LIST_DIR}/H5detect.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dfarray.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dfill.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dio.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dlayout.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dmpio.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dnone.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Doh.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dscatgath.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dselect.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dsingle.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dtest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Dvirtual.c
    ${CMAKE_CURRENT_LIST_DIR}/H5E.c
    ${CMAKE_CURRENT_LIST_DIR}/H5EA.c
    ${CMAKE_CURRENT_LIST_DIR}/H5EAcache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5EAdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5EAdblkpage.c
    ${CMAKE_CURRENT_LIST_DIR}/H5EAdblock.c
    ${CMAKE_CURRENT_LIST_DIR}/H5EAhdr.c
    ${CMAKE_CURRENT_LIST_DIR}/H5EAiblock.c
    ${CMAKE_CURRENT_LIST_DIR}/H5EAint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5EAsblock.c
    ${CMAKE_CURRENT_LIST_DIR}/H5EAstat.c
    ${CMAKE_CURRENT_LIST_DIR}/H5EAtest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Edeprec.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Eint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5F.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FA.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FAcache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Faccum.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FAdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FAdblkpage.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FAdblock.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FAhdr.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FAint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FAstat.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FAtest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fcwfs.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FD.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDcore.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDdirect.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fdeprec.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDfamily.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDlog.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDmpi.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDmpio.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDmulti.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDsec2.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDspace.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDstdio.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDtest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FDwindows.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fefc.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ffake.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fio.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FL.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fmount.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fmpi.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FO.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fquery.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FS.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FScache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FSdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fsfile.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FSint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fspace.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FSsection.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FSstat.c
    ${CMAKE_CURRENT_LIST_DIR}/H5FStest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fsuper.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Fsuper_cache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ftest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5G.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gbtree2.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gcache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gcompact.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gdense.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gdeprec.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gent.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Glink.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gloc.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gname.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gnode.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gobj.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Goh.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Groot.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gstab.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gtest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Gtraverse.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HF.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFbtree2.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFcache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFdblock.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFdtable.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFhdr.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFhuge.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFiblock.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFiter.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFman.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFsection.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFspace.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFstat.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFtest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HFtiny.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HG.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HGcache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HGdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HGquery.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HL.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HLcache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HLdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HLdblk.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HLint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HLprfx.c
    ${CMAKE_CURRENT_LIST_DIR}/H5HP.c
    ${CMAKE_CURRENT_LIST_DIR}/H5I.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Itest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5L.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Lexternal.c
    #${CMAKE_CURRENT_LIST_DIR}/H5make_libsettings.c
    ${CMAKE_CURRENT_LIST_DIR}/H5MF.c
    ${CMAKE_CURRENT_LIST_DIR}/H5MFaggr.c
    ${CMAKE_CURRENT_LIST_DIR}/H5MFdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5MFsection.c
    ${CMAKE_CURRENT_LIST_DIR}/H5MM.c
    ${CMAKE_CURRENT_LIST_DIR}/H5MP.c
    ${CMAKE_CURRENT_LIST_DIR}/H5MPtest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5O.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Oainfo.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Oalloc.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Oattr.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Oattribute.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Obogus.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Obtreek.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ocache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ocache_image.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ochunk.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ocont.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ocopy.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Odbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Odeprec.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Odrvinfo.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Odtype.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Oefl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ofill.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Oflush.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ofsinfo.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Oginfo.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Oint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Olayout.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Olinfo.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Olink.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Omessage.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Omtime.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Oname.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Onull.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Opline.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Orefcount.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Osdspace.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Oshared.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Oshmesg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ostab.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Otest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ounknown.c
    ${CMAKE_CURRENT_LIST_DIR}/H5P.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pacpl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5PB.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pdapl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pdcpl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pdeprec.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pdxpl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pencdec.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pfapl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pfcpl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pfmpl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pgcpl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5PL.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Plapl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Plcpl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5PLint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5PLpath.c
    ${CMAKE_CURRENT_LIST_DIR}/H5PLplugin_cache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pocpl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pocpypl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Pstrcpl.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ptest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5R.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Rdeprec.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Rint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5RS.c
    ${CMAKE_CURRENT_LIST_DIR}/H5S.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Sall.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Sdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Shyper.c
    ${CMAKE_CURRENT_LIST_DIR}/H5SL.c
    ${CMAKE_CURRENT_LIST_DIR}/H5SM.c
    ${CMAKE_CURRENT_LIST_DIR}/H5SMbtree2.c
    ${CMAKE_CURRENT_LIST_DIR}/H5SMcache.c
    ${CMAKE_CURRENT_LIST_DIR}/H5SMmessage.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Smpio.c
    ${CMAKE_CURRENT_LIST_DIR}/H5SMtest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Snone.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Spoint.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Sselect.c
    ${CMAKE_CURRENT_LIST_DIR}/H5ST.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Stest.c
    ${CMAKE_CURRENT_LIST_DIR}/H5system.c
    ${CMAKE_CURRENT_LIST_DIR}/H5T.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tarray.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tbit.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tcommit.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tcompound.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tconv.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tcset.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tdbg.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tdeprec.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tenum.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tfields.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tfixed.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tfloat.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tinit.c
    ${CMAKE_CURRENT_LIST_DIR}/H5timer.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tnative.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Toffset.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Toh.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Topaque.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Torder.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tpad.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tprecis.c
    ${CMAKE_CURRENT_LIST_DIR}/H5trace.c
    ${CMAKE_CURRENT_LIST_DIR}/H5TS.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tstrpad.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tvisit.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Tvlen.c
    ${CMAKE_CURRENT_LIST_DIR}/H5UC.c
    ${CMAKE_CURRENT_LIST_DIR}/H5VM.c
    ${CMAKE_CURRENT_LIST_DIR}/H5WB.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Z.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Zdeflate.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Zfletcher32.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Znbit.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Zscaleoffset.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Zshuffle.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Zszip.c
    ${CMAKE_CURRENT_LIST_DIR}/H5Ztrans.c
)
