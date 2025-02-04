/**
 * @file src/fileinfo/file_information/file_information.h
 * @brief Definition of FileInformation class.
 * @copyright (c) 2017 Avast Software, licensed under the MIT license
 */

#ifndef FILEINFO_FILE_INFORMATION_FILE_INFORMATION_H
#define FILEINFO_FILE_INFORMATION_FILE_INFORMATION_H

#include <optional>

#include "retdec/cpdetect/cpdetect.h"
#include "fileinfo/file_information/file_information_types/file_information_types.h"

namespace retdec {
namespace fileinfo {

/**
 * Class representing information about file
 *
 * Value std::numeric_limits<unsigned long long>::max() mean unspecified value or error for numeric types.
 * Methods with index parameters does not perform control of indexes.
 */
class FileInformation
{
	private:
		retdec::cpdetect::ReturnCode status = retdec::cpdetect::ReturnCode::OK;
		std::string filePath;                          ///< path to input file
		std::string telfhash;                          ///< telfhash of ELF input file
		std::string crc32;                             ///< CRC32 of input file
		std::string md5;                               ///< MD5 of input file
		std::string sha256;                            ///< SHA256 of input file
		std::string secCrc32;                          ///< CRC32 of section table
		std::string secMd5;                            ///< MD5 of section table
		std::string secSha256;                         ///< SHA256 of section table
		/// format of input file in enumeration representation
		retdec::fileformat::Format fileFormatEnum = retdec::fileformat::Format::UNKNOWN;
		std::string fileFormat;                        ///< format of input file in string representation
		std::string fileClass;                         ///< class of file
		std::string fileType;                          ///< type of file (e.g. executable file)
		std::string targetArchitecture;                ///< target architecture
		std::string endianness;                        ///< endianness
		std::string manifest;                          ///< XML manifest
		std::string compactManifest;                   ///< compact version of XML manifest
		FileHeader header;                             ///< file header
		RichHeader richHeader;                         ///< rich header
		VisualBasicInfo visualBasicInfo;               ///< visual basic information
		PdbInfo pdbInfo;                               ///< information about related PDB file
		ImportTable importTable;                       ///< information about imports
		ExportTable exportTable;                       ///< information about exports
		ResourceTable resourceTable;                   ///< information about resources in input file
		TlsInfo tlsInfo;                               ///< information about thread-local storage
		ElfCore elfCoreInfo;                           ///< information about ELF core files
		LoaderInfo loaderInfo;                         ///< information about loaded image
		std::vector<DataDirectory> directories;        ///< information about data directories
		std::vector<FileSegment> segments;             ///< information about segments in file
		std::vector<FileSection> sections;             ///< information about sections in file
		std::vector<SymbolTable> symbolTables;         ///< symbol tables
		std::vector<RelocationTable> relocationTables; ///< relocation tables
		std::vector<DynamicSection> dynamicSections;   ///< information about dynamic sections
		std::vector<ElfNotes> elfNotes;                ///< information about ELF sections
		std::vector<Pattern> cryptoPatterns;           ///< detected crypto patterns
		std::vector<Pattern> malwarePatterns;          ///< detected malware patterns
		std::vector<Pattern> otherPatterns;            ///< other detected patterns
		Strings strings;                               ///< detected strings
		std::optional<bool> signatureVerified;         ///< indicates whether the signature is present and if it is verified
		DotnetInfo dotnetInfo;                         ///< .NET information
		std::string failedDepsList;                    /// If non-empty, trhis contains the name of the dependency list that failed to load
		std::vector<std::pair<std::string,std::string>> anomalies;     ///< detected anomalies

	public:
		const retdec::fileformat::CertificateTable* certificateTable = nullptr; ///< information about signatures
		retdec::fileformat::PeTimestamps pe_timestamps; ///< Various Timestamps stored in PE file
		retdec::cpdetect::ToolInformation toolInfo; ///< detected tools
		std::vector<std::string> messages;   ///< error, warning and other messages

		/// @name Getters of own members
		/// @{
		retdec::cpdetect::ReturnCode getStatus() const;
		std::string getPathToFile() const;
		std::string getTelfhash() const;
		std::string getCrc32() const;
		std::string getMd5() const;
		std::string getSha256() const;
		std::string getSectionTableCrc32() const;
		std::string getSectionTableMd5() const;
		std::string getSectionTableSha256() const;
		retdec::fileformat::Format getFileFormatEnum() const;
		std::string getFileFormat() const;
		std::string getFileClass() const;
		std::string getFileType() const;
		std::string getTargetArchitecture() const;
		std::string getEndianness() const;
		std::string getManifest() const;
		std::string getCompactManifest() const;
		std::size_t getNumberOfStoredDataDirectories() const;
		std::size_t getNumberOfStoredSegments() const;
		std::size_t getNumberOfStoredSections() const;
		std::size_t getNumberOfStoredSymbolTables() const;
		std::size_t getNumberOfStoredRelocationTables() const;
		std::size_t getNumberOfStoredDynamicSections() const;
		std::size_t getNumberOfLoadedSegments() const;
		std::size_t getNumberOfCryptoPatterns() const;
		std::size_t getNumberOfMalwarePatterns() const;
		std::size_t getNumberOfOtherPatterns() const;
		/// @}

		/// @name Getters of @a header
		/// @{
		std::string getTimeStamp() const;
		std::string getFileStatus() const;
		std::string getFileVersion() const;
		std::string getFileHeaderVersion() const;
		std::string getOsAbi() const;
		std::string getOsAbiVersion() const;
		unsigned long long getFileFlagsSize() const;
		unsigned long long getFileFlags() const;
		std::string getFileFlagsStr() const;
		std::size_t getNumberOfFileFlagsDescriptors() const;
		void getFileFlagsDescriptors(std::vector<std::string> &desc, std::vector<std::string> &abb) const;
		unsigned long long getDllFlagsSize() const;
		unsigned long long getDllFlags() const;
		std::string getDllFlagsStr() const;
		std::size_t getNumberOfDllFlagsDescriptors() const;
		void getDllFlagsDescriptors(std::vector<std::string> &desc, std::vector<std::string> &abb) const;
		std::string getNumberOfBitsInByteStr() const;
		std::string getNumberOfBitsInWordStr() const;
		std::string getFileHeaderSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSegmentTableOffsetStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSegmentTableEntrySizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSegmentTableSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getNumberOfDeclaredSegmentsStr() const;
		std::string getSectionTableOffsetStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSectionTableEntrySizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSectionTableSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getNumberOfDeclaredSectionsStr() const;
		std::string getCoffFileHeaderSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getOptionalHeaderSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getChecksumStr() const;
		std::string getStackReserveSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getStackCommitSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getHeapReserveSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getHeapCommitSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getNumberOfDeclaredDataDirectoriesStr() const;
		std::string getNumberOfDeclaredSymbolTablesStr() const;
		std::string getOverlayOffsetStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getOverlaySizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getOverlayEntropyStr(std::ios_base &(* format)(std::ios_base &)) const;
		/// @}

		/// @name Getters of @a richHeader
		/// @{
		std::size_t getNumberOfStoredRecordsInRichHeader() const;
		std::string getRichHeaderSignature() const;
		std::string getRichHeaderOffsetStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getRichHeaderKeyStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getRichHeaderRecordProductIdStr(std::size_t position) const;
		std::string getRichHeaderRecordProductBuildStr(std::size_t position) const;
		std::string getRichHeaderRecordNumberOfUsesStr(std::size_t position) const;
		std::string getRichHeaderRecordProductNameStr(std::size_t position) const;
		std::string getRichHeaderRecordVisualStudioNameStr(std::size_t position) const;
		std::string getRichHeaderRawBytesStr() const;
		std::string getRichHeaderSha256() const;
		std::string getRichHeaderCrc32() const;
		std::string getRichHeaderMd5() const;
		bool hasRichHeaderRecords() const;
		/// @}

		/// @name Getters of @a visualBasicInfo
		/// @{
		bool isVisualBasicUsed() const;
		bool getVisualBasicIsPcode() const;
		std::string getVisualBasicLanguageDLL() const;
		std::string getVisualBasicBackupLanguageDLL() const;
		std::string getVisualBasicProjectExeName() const;
		std::string getVisualBasicProjectDescription() const;
		std::string getVisualBasicProjectHelpFile() const;
		std::string getVisualBasicProjectName() const;
		std::string getVisualBasicLanguageDLLPrimaryLCIDStr() const;
		std::string getVisualBasicLanguageDLLSecondaryLCIDStr() const;
		std::string getVisualBasicProjectPath() const;
		std::string getVisualBasicProjectPrimaryLCIDStr() const;
		std::string getVisualBasicProjectSecondaryLCIDStr() const;
		const retdec::fileformat::VisualBasicObject *getVisualBasicObject(std::size_t position) const;
		const retdec::fileformat::VisualBasicExtern *getVisualBasicExtern(std::size_t position) const;
		std::size_t getVisualBasicNumberOfObjects() const;
		std::size_t getVisualBasicNumberOfExterns() const;
		std::string getVisualBasicExternModuleName(std::size_t position) const;
		std::string getVisualBasicExternApiName(std::size_t position) const;
		std::string getVisualBasicObjectTableGUID() const;
		std::string getVisualBasicTypeLibCLSID() const;
		std::string getVisualBasicTypeLibMajorVersionStr() const;
		std::string getVisualBasicTypeLibMinorVersionStr() const;
		std::string getVisualBasicTypeLibLCIDStr() const;
		std::string getVisualBasicCOMObjectName() const;
		std::string getVisualBasicCOMObjectDescription() const;
		std::string getVisualBasicCOMObjectCLSID() const;
		std::string getVisualBasicCOMObjectInterfaceCLSID() const;
		std::string getVisualBasicCOMObjectEventsCLSID() const;
		std::string getVisualBasicCOMObjectType() const;
		std::string getVisualBasicExternTableHashCrc32() const;
		std::string getVisualBasicExternTableHashMd5() const;
		std::string getVisualBasicExternTableHashSha256() const;
		std::string getVisualBasicObjectTableHashCrc32() const;
		std::string getVisualBasicObjectTableHashMd5() const;
		std::string getVisualBasicObjectTableHashSha256() const;
		/// @}

		/// @name Getters of @a pdbInfo
		/// @{
		std::string getPdbType() const;
		std::string getPdbPath() const;
		std::string getPdbGuid() const;
		std::string getPdbAgeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getPdbTimeStampStr(std::ios_base &(* format)(std::ios_base &)) const;
		/// @}

		/// @name Getters of @a importTable
		/// @{
		std::size_t getNumberOfStoredImportLibraries() const;
		std::size_t getNumberOfStoredImports() const;
		std::string getImphashCrc32() const;
		std::string getImphashMd5() const;
		std::string getImphashSha256() const;
		std::string getImphashTlsh() const;
		const retdec::fileformat::Import* getImport(std::size_t position) const;
		std::string getImportName(std::size_t position) const;
		std::string getImportLibraryName(std::size_t position) const;
		std::string getImportUsageType(std::size_t position) const;
		std::string getImportAddressStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getImportOrdinalNumberStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		bool hasImportTableRecords() const;
		/// @}

		/// @name Getters of the missing dependency info
		/// @{
		std::size_t getNumberOfMissingDeps() const;
		std::string getMissingDepName(std::size_t position) const;
		std::string getDepsListFailedToLoad() const;
		void setDepsListFailedToLoad(const std::string & );
		/// @}

		/// @name Getters of @a exportTable
		/// @{
		std::size_t getNumberOfStoredExports() const;
		std::string getExphashCrc32() const;
		std::string getExphashMd5() const;
		std::string getExphashSha256() const;
		std::string getExportName(std::size_t position) const;
		std::string getExportAddressStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getExportOrdinalNumberStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		bool hasExportTableRecords() const;
		/// @}

		/// @name Getters of @a resourceTable
		/// @{
		std::size_t getNumberOfStoredResources() const;
		std::size_t getNumberOfVersionInfoLanguages() const;
		std::size_t getNumberOfVersionInfoStrings() const;
		std::string getResourceCrc32(std::size_t index) const;
		std::string getResourceMd5(std::size_t index) const;
		std::string getResourceSha256(std::size_t index) const;
		std::string getResourceIconhashCrc32() const;
		std::string getResourceIconhashMd5() const;
		std::string getResourceIconhashSha256() const;
		std::string getResourceIconPerceptualAvgHash() const;
		std::string getResourceName(std::size_t index) const;
		std::string getResourceType(std::size_t index) const;
		std::string getResourceLanguage(std::size_t index) const;
		std::string getVersionInfoLanguageLcid(std::size_t index) const;
		std::string getVersionInfoLanguageCodePage(std::size_t index) const;
		std::string getVersionInfoStringName(std::size_t index) const;
		std::string getVersionInfoStringValue(std::size_t index) const;
		std::string getResourceNameIdStr(std::size_t index, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getResourceTypeIdStr(std::size_t index, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getResourceLanguageIdStr(std::size_t index, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getResourceSublanguageIdStr(std::size_t index, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getResourceOffsetStr(std::size_t index, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getResourceSizeStr(std::size_t index, std::ios_base &(* format)(std::ios_base &)) const;
		bool hasResourceTableRecords() const;
		/// @}

		/// @name Getters of @a TLS information
		/// @{
		std::string getTlsRawDataStartAddrStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getTlsRawDataEndAddrStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getTlsIndexAddrStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getTlsCallBacksAddrStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getTlsZeroFillSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getTlsCharacteristicsStr() const;
		std::size_t getTlsNumberOfCallBacks() const;
		std::string getTlsCallBackAddrStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		bool isTlsUsed() const;
		/// @}

		/// @name Getters of @a directories
		/// @{
		std::string getDataDirectoryType(std::size_t position) const;
		std::string getDataDirectoryAddressStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getDataDirectorySizeStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		/// @}

		/// @name Getters of @a segments
		/// @{
		std::string getSegmentType(std::size_t position) const;
		std::string getSegmentCrc32(std::size_t index) const;
		std::string getSegmentMd5(std::size_t index) const;
		std::string getSegmentSha256(std::size_t index) const;
		std::string getSegmentIndexStr(std::size_t position) const;
		std::string getSegmentOffsetStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSegmentVirtualAddressStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSegmentPhysicalAddressStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSegmentSizeInFileStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSegmentSizeInMemoryStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSegmentAlignmentStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		unsigned long long getSegmentFlagsSize(std::size_t position) const;
		unsigned long long getSegmentFlags(std::size_t position) const;
		std::string getSegmentFlagsStr(std::size_t position) const;
		std::size_t getNumberOfSegmentFlagsDescriptors(std::size_t position) const;
		void getSegmentFlagsDescriptors(std::size_t position, std::vector<std::string> &desc, std::vector<std::string> &abb) const;
		/// @}

		/// @name Getters of @a sections
		/// @{
		std::string getSectionName(std::size_t position) const;
		std::string getSectionType(std::size_t position) const;
		std::string getSectionCrc32(std::size_t index) const;
		std::string getSectionMd5(std::size_t index) const;
		std::string getSectionSha256(std::size_t index) const;
		std::string getSectionIndexStr(std::size_t position) const;
		std::string getSectionOffsetStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSectionSizeInFileStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSectionEntrySizeStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSectionAddressStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSectionSizeInMemoryStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSectionRelocationsOffsetStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSectionNumberOfRelocationsStr(std::size_t position) const;
		std::string getSectionLineNumbersOffsetStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSectionNumberOfLineNumbersStr(std::size_t position) const;
		std::string getSectionMemoryAlignmentStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSectionLinkToOtherSectionStr(std::size_t position) const;
		std::string getSectionExtraInfoStr(std::size_t position) const;
		std::string getSectionLineOffsetStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSectionRelocationsLineOffsetStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSectionEntropy(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		unsigned long long getSectionFlagsSize(std::size_t position) const;
		unsigned long long getSectionFlags(std::size_t position) const;
		std::string getSectionFlagsStr(std::size_t position) const;
		std::size_t getNumberOfSectionFlagsDescriptors(std::size_t position) const;
		void getSectionFlagsDescriptors(std::size_t position, std::vector<std::string> &desc, std::vector<std::string> &abb) const;
		/// @}

		/// @name Getters of @a symbolTables
		/// @{
		std::size_t getNumberOfStoredSymbolsInTable(std::size_t position) const;
		std::string getNumberOfDeclaredSymbolsInTableStr(std::size_t position) const;
		std::string getSymbolTableName(std::size_t position) const;
		std::string getSymbolTableOffsetStr(std::size_t position, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSymbolName(std::size_t tableIndex, std::size_t symbolIndex) const;
		std::string getSymbolType(std::size_t tableIndex, std::size_t symbolIndex) const;
		std::string getSymbolBind(std::size_t tableIndex, std::size_t symbolIndex) const;
		std::string getSymbolOther(std::size_t tableIndex, std::size_t symbolIndex) const;
		std::string getSymbolLinkToSection(std::size_t tableIndex, std::size_t symbolIndex) const;
		std::string getSymbolIndexStr(std::size_t tableIndex, std::size_t symbolIndex) const;
		std::string getSymbolAddressStr(std::size_t tableIndex, std::size_t symbolIndex, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getSymbolValueStr(std::size_t tableIndex, std::size_t symbolIndex) const;
		std::string getSymbolSizeStr(std::size_t tableIndex, std::size_t symbolIndex) const;
		std::size_t getSymbolTableNumberOfStoredSpecialInformation(std::size_t position) const;
		std::size_t getSymbolTableNumberOfSpecialInformationValues(std::size_t tableIndex, std::size_t specInfoIndex) const;
		std::string getSymbolTableSpecialInformationDescription(std::size_t tableIndex, std::size_t specInfoIndex) const;
		std::string getSymbolTableSpecialInformationAbbreviation(std::size_t tableIndex, std::size_t specInfoIndex) const;
		std::string getSymbolTableSpecialInformationValue(std::size_t tableIndex, std::size_t specInfoIndex, std::size_t recordIndex) const;
		/// @}

		/// @name Getters of @a relocationTables
		/// @{
		std::size_t getNumberOfStoredRelocationsInTable(std::size_t position) const;
		std::string getNumberOfStoredRelocationsInTableStr(std::size_t position) const;
		std::string getNumberOfDeclaredRelocationsInTableStr(std::size_t position) const;
		std::string getRelocationTableName(std::size_t position) const;
		std::string getRelocationTableAssociatedSymbolTableName(std::size_t position) const;
		std::string getRelocationTableAppliesSectionName(std::size_t position) const;
		std::string getRelocationTableAssociatedSymbolTableIndex(std::size_t position) const;
		std::string getRelocationTableAppliesSectionIndex(std::size_t position) const;
		std::string getRelocationSymbolName(std::size_t tableIndex, std::size_t relocationIndex) const;
		std::string getRelocationOffsetStr(std::size_t tableIndex, std::size_t relocationIndex, std::ios_base &(* format)(std::ios_base &)) const;
		std::string getRelocationSymbolValueStr(std::size_t tableIndex, std::size_t relocationIndex) const;
		std::string getRelocationTypeStr(std::size_t tableIndex, std::size_t relocationIndex) const;
		std::string getRelocationAddendStr(std::size_t tableIndex, std::size_t relocationIndex) const;
		std::string getRelocationCalculatedValueStr(std::size_t tableIndex, std::size_t relocationIndex) const;
		/// @}

		/// @name Getters of @a dynamicSections
		/// @{
		std::size_t getNumberOfStoredDynamicEntriesInSection(std::size_t position) const;
		std::string getNumberOfDeclaredDynamicEntriesInSectionStr(std::size_t position) const;
		std::string getDynamicSectionName(std::size_t position) const;
		std::string getDynamicEntryType(std::size_t sectionIndex, std::size_t entryIndex) const;
		std::string getDynamicEntryDescription(std::size_t sectionIndex, std::size_t entryIndex) const;
		std::string getDynamicEntryValueStr(std::size_t sectionIndex, std::size_t entryIndex, std::ios_base &(* format)(std::ios_base &)) const;
		unsigned long long getDynamicEntryFlagsSize(std::size_t sectionIndex, std::size_t entryIndex) const;
		unsigned long long getDynamicEntryFlags(std::size_t sectionIndex, std::size_t entryIndex) const;
		std::string getDynamicEntryFlagsStr(std::size_t sectionIndex, std::size_t entryIndex) const;
		std::size_t getNumberOfDynamicEntryFlagsDescriptors(std::size_t sectionIndex, std::size_t entryIndex) const;
		void getDynamicEntryFlagsDescriptors(std::size_t sectionIndex, std::size_t entryIndex, std::vector<std::string> &desc, std::vector<std::string> &abb) const;
		/// @}

		/// @name Pattern getters
		/// @{
		const Pattern* getCryptoPattern(std::size_t position) const;
		const Pattern* getMalwarePattern(std::size_t position) const;
		const Pattern* getOtherPattern(std::size_t position) const;
		const std::vector<Pattern>& getCryptoPatterns() const;
		const std::vector<Pattern>& getMalwarePatterns() const;
		const std::vector<Pattern>& getOtherPatterns() const;
		/// @}

		/// @name Getters of @a strings
		/// @{
		std::size_t getNumberOfDetectedStrings() const;
		const Strings& getStrings() const;
		bool hasStrings() const;
		/// @}

		/// @name Getter of @a signatureVerified
		/// @{
		bool isSignaturePresent() const;
		bool isSignatureVerified() const;
		std::string isSignatureVerifiedStr(const std::string& t = "true", const std::string& f = "false") const;
		/// @}

		/// @name Getter of @a elfNotes and associtated structures
		/// @{
		const std::vector<ElfNotes>& getElfNotes() const;
		const ElfCore& getElfCoreInfo() const;
		/// @}

		/// @name Getters of @a compilerOrPackerInfo
		/// @{
		std::size_t getNumberOfDetectedCompilers() const;
		std::string getImageBaseStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getEpAddressStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getEpOffsetStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getEpBytes() const;
		std::string getEpSectionIndex() const;
		std::string getEpSectionName() const;
		/// @}

		/// @name Getters of @a loaderInfo
		/// @{
		std::string getLoadedBaseAddressStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getNumberOfLoadedSegmentsStr(std::ios_base &(* format)(std::ios_base &)) const;
		const LoadedSegment& getLoadedSegment(std::size_t index) const;
		const std::string& getLoaderStatusMessage() const;
		const retdec::fileformat::LoaderErrorInfo & getLoaderErrorInfo() const;
	    /// @}

		/// @name Getters of @a dotnetInfo
		/// @{
		bool isDotnetUsed() const;
		const std::string& getDotnetRuntimeVersion() const;
		std::string getDotnetImportedClassName(std::size_t position) const;
		std::string getDotnetImportedClassNestedName(std::size_t position) const;
		std::string getDotnetImportedClassNameWithParentClassIndex(std::size_t position) const;
		std::string getDotnetImportedClassLibName(std::size_t position) const;
		std::string getDotnetImportedClassNameSpace(std::size_t position) const;
		std::string getDotnetTypeRefhashCrc32() const;
		std::string getDotnetTypeRefhashMd5() const;
		std::string getDotnetTypeRefhashSha256() const;
		std::size_t getNumberOfStoredDotnetImportedClasses() const;
		std::string getDotnetMetadataHeaderAddressStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getDotnetMetadataStreamOffsetStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getDotnetMetadataStreamSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getDotnetStringStreamOffsetStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getDotnetStringStreamSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getDotnetBlobStreamOffsetStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getDotnetBlobStreamSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getDotnetGuidStreamOffsetStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getDotnetGuidStreamSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getDotnetUserStringStreamOffsetStr(std::ios_base &(* format)(std::ios_base &)) const;
		std::string getDotnetUserStringStreamSizeStr(std::ios_base &(* format)(std::ios_base &)) const;
		const std::string& getDotnetModuleVersionId() const;
		const std::string& getDotnetTypeLibId() const;
		const std::vector<std::shared_ptr<retdec::fileformat::DotnetClass>>& getDotnetDefinedClassList() const;
		const std::vector<std::shared_ptr<retdec::fileformat::DotnetClass>>& getDotnetImportedClassList() const;
		bool hasDotnetMetadataStream() const;
		bool hasDotnetStringStream() const;
		bool hasDotnetBlobStream() const;
		bool hasDotnetGuidStream() const;
		bool hasDotnetUserStringStream() const;
		bool hasDotnetTypeLibId() const;
		bool hasDotnetTypeRefTableRecords() const;
		/// @}

		/// @name Getters of @a anomalies
		/// @{
		std::size_t getNumberOfAnomalies() const;
		std::string getAnomalyIdentifier(std::size_t position) const;
		std::string getAnomalyDescription(std::size_t position) const;
		/// @}

		/// @name Setters
		/// @{
		void setStatus(retdec::cpdetect::ReturnCode state);
		void setPathToFile(const std::string &filepath);
		void setTelfhash(const std::string &telfhash);
		void setCrc32(const std::string &fileCrc32);
		void setMd5(const std::string &fileMd5);
		void setSha256(const std::string &fileSha256);
		void setSectionTableCrc32(const std::string &sCrc32);
		void setSectionTableMd5(const std::string &sMd5);
		void setSectionTableSha256(const std::string &sSha256);
		void setFileFormatEnum(retdec::fileformat::Format format);
		void setFileFormat(const std::string &fileformat);
		void setFileClass(const std::string &fileclass);
		void setFileType(const std::string &filetype);
		void setTargetArchitecture(const std::string &architecture);
		void setEndianness(const std::string &fileEndianness);
		void setManifest(const std::string &fileManifest);
		void setCompactManifest(const std::string &fileCompactManifest);
		void setTimeStamp(const std::string &timestamp);
		void setFileStatus(const std::string &fileStatus);
		void setFileVersion(const std::string &version);
		void setFileHeaderVersion(const std::string &version);
		void setOsAbi(const std::string &osabi);
		void setOsAbiVersion(const std::string &abiversion);
		void setFileFlagsSize(unsigned long long size);
		void setFileFlags(unsigned long long flagsArray);
		void setDllFlagsSize(unsigned long long size);
		void setDllFlags(unsigned long long flagsArray);
		void setNumberOfBitsInByte(unsigned long long bitsInByte);
		void setNumberOfBitsInWord(unsigned long long bitsInWord);
		void setFileHeaderSize(unsigned long long size);
		void setSegmentTableOffset(unsigned long long offset);
		void setSegmentTableEntrySize(unsigned long long entrySize);
		void setSegmentTableSize(unsigned long long tableSize);
		void setNumberOfDeclaredSegments(unsigned long long noOfSegments);
		void setSectionTableOffset(unsigned long long offset);
		void setSectionTableEntrySize(unsigned long long entrySize);
		void setSectionTableSize(unsigned long long tableSize);
		void setNumberOfDeclaredSections(unsigned long long noOfSections);
		void setCoffFileHeaderSize(unsigned long long headerSize);
		void setOptionalHeaderSize(unsigned long long headerSize);
		void setChecksum(unsigned long long fileChecksum);
		void setStackReserveSize(unsigned long long size);
		void setStackCommitSize(unsigned long long size);
		void setHeapReserveSize(unsigned long long size);
		void setHeapCommitSize(unsigned long long size);
		void setNumberOfDeclaredDataDirectories(unsigned long long noOfDirectories);
		void setNumberOfDeclaredSymbolTables(unsigned long long noOfTables);
		void setOverlayOffset(unsigned long long offset);
		void setOverlaySize(unsigned long long size);
		void setOverlayEntropy(double entropy);
		void setRichHeader(const retdec::fileformat::RichHeader *rHeader);
		void setVisualBasicInfo(const retdec::fileformat::VisualBasicInfo *vbInfo);
		void setVisualBasicUsed(bool set);
		void setPdbType(const std::string &sType);
		void setPdbPath(const std::string &sPath);
		void setPdbGuid(const std::string &sGuid);
		void setPdbAge(std::size_t sAge);
		void setPdbTimeStamp(std::size_t sTimeStamp);
		void setImportTable(const retdec::fileformat::ImportTable *sTable);
		void setExportTable(const retdec::fileformat::ExportTable *sTable);
		void setResourceTable(const retdec::fileformat::ResourceTable *sTable);
		void setStrings(const std::vector<retdec::fileformat::String> *sStrings);
		void setCertificateTable(const retdec::fileformat::CertificateTable *sTable);
		void setTlsInfo(const retdec::fileformat::TlsInfo *info);
		void setSignatureVerified(bool verified);
		void setLoadedBaseAddress(unsigned long long baseAddress);
		void setLoaderStatusMessage(const std::string& statusMessage);
		void setLoaderErrorInfo(const retdec::fileformat::LoaderErrorInfo & ldrErrInfo);
		void setDotnetUsed(bool set);
		void setDotnetRuntimeVersion(std::uint64_t majorVersion, std::uint64_t minorVersion);
		void setDotnetMetadataHeaderAddress(std::uint64_t address);
		void setDotnetMetadataStreamInfo(std::uint64_t streamOffset, std::uint64_t streamSize);
		void setDotnetStringStreamInfo(std::uint64_t streamOffset, std::uint64_t streamSize);
		void setDotnetBlobStreamInfo(std::uint64_t streamOffset, std::uint64_t streamSize);
		void setDotnetGuidStreamInfo(std::uint64_t streamOffset, std::uint64_t streamSize);
		void setDotnetUserStringStreamInfo(std::uint64_t streamOffset, std::uint64_t streamSize);
		void setDotnetModuleVersionId(const std::string& moduleVersionId);
		void setDotnetTypeLibId(const std::string& typeLibId);
		void setDotnetDefinedClassList(const std::vector<std::shared_ptr<retdec::fileformat::DotnetClass>>& dotnetClassList);
		void setDotnetImportedClassList(const std::vector<std::shared_ptr<retdec::fileformat::DotnetClass>>& dotnetClassList);
		void setDotnetTypeRefhashCrc32(const std::string& crc32);
		void setDotnetTypeRefhashMd5(const std::string& md5);
		void setDotnetTypeRefhashSha256(const std::string& sha256);
		void setAnomalies(const std::vector<std::pair<std::string,std::string>> &anom);
		/// @}

		/// @name Other methods
		/// @{
		void addFileFlagsDescriptor(std::string descriptor, std::string abbreviation);
		void clearFileFlagsDescriptors();
		void addDllFlagsDescriptor(std::string descriptor, std::string abbreviation);
		void clearDllFlagsDescriptors();
		void addDataDirectory(DataDirectory &dataDirectory);
		void addSegment(FileSegment &fileSegment);
		void addSection(FileSection &fileSection);
		void addSymbolTable(SymbolTable &table);
		void addRelocationTable(RelocationTable &table);
		void addDynamicSection(DynamicSection &section);
		void addElfNotes(ElfNotes &notes);
		void addFileMapEntry(const FileMapEntry& entry);
		void addAuxVectorEntry(const std::string& name, std::size_t value);
		void addCryptoPattern(Pattern &pattern);
		void removeRedundantCryptoRules();
		void sortCryptoPatternMatches();
		void addMalwarePattern(Pattern &pattern);
		void sortMalwarePatternMatches();
		void addOtherPattern(Pattern &pattern);
		void sortOtherPatternMatches();
		void addTool(retdec::cpdetect::DetectResult &tool);
		void addLoadedSegment(const LoadedSegment& segment);
		/// @}
};

} // namespace fileinfo
} // namespace retdec

#endif
