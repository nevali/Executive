#ifndef SIMULATOR_INTERNAL_DIAGNOSTICS_H_
# define SIMULATOR_INTERNAL_DIAGNOSTICS_H_ 1

# include <PAL/PAL.h>

namespace PAL
{
	namespace Simulator
	{
		class Diagnostics: public IPlatformDiagnostics, public IWriteChannel
		{
		private:
			LogLevel level_;
		public:
			/* Constructor */
			Diagnostics();
		public:
			/* Internal helpers */
			void vlogf(LogLevel level, const char *format, va_list args);
			void panic(PHASE phase, const char *str);
		public:
			/* IObject */
			virtual STATUS queryInterface(REFUUID iid, void **out);

			virtual REFCOUNT retain(void)
			{
				/* the Diagnostics object is always a singleton */
				return 2;
			}

			virtual REFCOUNT release(void)
			{
				return 1;
			}
		public:
			/* IPlatformDiagnostics */
			virtual void log(LogLevel level, const char *str);
		public:
			/* IWriteChannel */
			virtual size_t write(const uint8_t *buf, size_t nbytes);
		private:
			void setEnvironmentLogLevel(void);
			const char *logPrefix(LogLevel level);
		};
	}
}

#endif /*!SIMULATOR_INTERNAL_DIAGNOSTICS_H_*/
